#include "mainwindow.h"
#include "createform.h"
#include "editform.h"
#include "ui_mainwindow.h"
#include <QStandardPaths>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , board(new Board(this))
{
    ui->setupUi(this);
    setWindowTitle("Kanban App");
    fileName = "kanban.json";
    board->loadFromFile(fileName);
    connectSignals();
    ui->todoList->setStatus(Status::ToDo);
    ui->inProgressList->setStatus(Status::InProgress);
    ui->doneList->setStatus(Status::Done);
    ui->todoList->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->inProgressList->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->doneList->setContextMenuPolicy(Qt::CustomContextMenu);

    for (const Task &task : board->getTasks()) {
        addTaskToUI(task);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectSignals() {
    connect(board, &Board::taskAdded, this, &MainWindow::onTaskAdded);
    connect(board, &Board::taskRemoved, this, &MainWindow::onTaskRemoved);
    connect(board, &Board::taskUpdated, this, &MainWindow::onTaskUpdated);
    connect(ui->todoList, &KanbanListWidget::taskDropped, this, &MainWindow::onTaskDropped);
    connect(ui->inProgressList, &KanbanListWidget::taskDropped, this, &MainWindow::onTaskDropped);
    connect(ui->doneList, &KanbanListWidget::taskDropped, this, &MainWindow::onTaskDropped);
    connect(ui->todoList, &QWidget::customContextMenuRequested, this, &MainWindow::showContextMenu);
    connect(ui->inProgressList, &QWidget::customContextMenuRequested, this, &MainWindow::showContextMenu);
    connect(ui->doneList, &QWidget::customContextMenuRequested, this, &MainWindow::showContextMenu);

}

void MainWindow::addTaskToUI(const Task &task) {
    KanbanListWidget *list = nullptr;
    switch (task.status) {
        case Status::ToDo: list = ui->todoList; break;
        case Status::InProgress: list = ui->inProgressList; break;
        case Status::Done: list = ui->doneList; break;
    }
    if (list) {
        QListWidgetItem *item = new QListWidgetItem(task.title);
        item->setData(Qt::UserRole, task.id);
        std::string icon;
        switch (task.priority) {
            case Priority::Low:     icon = "low"; break;
            case Priority::Medium:  icon = "medium"; break;
            case Priority::High:    icon = "high"; break;
        }
        QString iconPath = QString::fromStdString(":/icons/" + icon + ".png");
        QIcon iconEl(iconPath);
        item->setIcon(iconEl);
        item->setText(item->text() + "\n" + task.createdAt.toString("dd.MM.yyyy HH:mm"));
        list->addItem(item);
    }
}

void MainWindow::onTaskAdded(const Task &task) {
    addTaskToUI(task);
    board->saveToFile(fileName);
}

void MainWindow::onTaskUpdated(const Task &task) {
    QList<KanbanListWidget*> lists = { ui->todoList, ui->inProgressList, ui->doneList };
    for (KanbanListWidget *list : lists) {
        for (int i = 0; i < list->count(); ++i) {
            auto *item = list->item(i);
            if (item->data(Qt::UserRole).toUuid() == task.id) {
                delete list->takeItem(i);
                addTaskToUI(task);
                board->saveToFile(fileName);
                return;
            }
        }
    }
}

void MainWindow::onTaskRemoved(const QUuid &id) {
    QList<KanbanListWidget*> lists = { ui->todoList, ui->inProgressList, ui->doneList };
    for (KanbanListWidget *list : lists) {
        for (int i = 0; i < list->count(); ++i) {
            auto *item = list->item(i);
            if (item->data(Qt::UserRole).toUuid() == id) {
                delete list->takeItem(i);
                board->saveToFile(fileName);
                return;
            }
        }
    }
}

void MainWindow::on_addBtn_clicked()
{
    CreateForm form(this);
    if (form.exec() == QDialog::Accepted) {
        QString title = form.getTitle();
        QString description = form.getDescription();
        Task task(title, description);
        board->addTask(task);
    }
}

void MainWindow::onTaskDropped(const QUuid &id, Status newStatus){
    Task *task = board->getTaskById(id);
    if (task && task->status != newStatus) {
        task->status = newStatus;
        board->saveToFile(fileName);
    }
}

void MainWindow::showContextMenu(const QPoint &pos)
{
    QListWidget* list = qobject_cast<QListWidget*>(sender());
    QListWidgetItem* item = list->itemAt(pos);
    if (!item)
        return;

    QMenu contextMenu(this);
    QAction* editAction = contextMenu.addAction(QIcon(":/icons/edit.png"), "Edit");
    QAction* deleteAction = contextMenu.addAction(QIcon(":/icons/delete.png"), "Delete");

    QAction* selectedAction = contextMenu.exec(list->viewport()->mapToGlobal(pos));
    if (!selectedAction)
        return;

    if (selectedAction == editAction) {
        QUuid taskId = item->data(Qt::UserRole).toUuid();
        Task* task = board->getTaskById(taskId);

        if (!task) return;

        QString currentTitle = task->title;
        QString currentDescription = task->description;
        Priority currentPriority = task->priority;

        EditForm dlg(this);
        dlg.setTitle(currentTitle);
        dlg.setDescription(currentDescription);
        dlg.setPriority(currentPriority);

        if (dlg.exec() == QDialog::Accepted) {
            QString newTitle = dlg.getTitle();
            QString newDesc = dlg.getDescription();
            Priority newPriority = dlg.getPriority();
            Task newTask(newTitle, newDesc, task->status, newPriority);
            board->updateTask(task, newTask);
        }
    }
    else if (selectedAction == deleteAction) {
        QUuid taskId = item->data(Qt::UserRole).toUuid();
        Task* task = board->getTaskById(taskId);

        if (task) {
            board->removeTask(taskId);
        }
    }
}
