#include "mainwindow.h"
#include "createform.h"
#include "editform.h"
#include "ui_mainwindow.h"
#include <QStandardPaths>
#include <QFileDialog>
#include <QMenu>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , board(new Board(this))
    , reloadBtn(nullptr)
{
    ui->setupUi(this);
    connectSignals();
    setWindowTitle("Kanban App");
    fileName = "kanban.json";
    
    // Set up list properties before loading
    ui->todoList->setStatus(Status::ToDo);
    ui->inProgressList->setStatus(Status::InProgress);
    ui->doneList->setStatus(Status::Done);
    ui->todoList->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->inProgressList->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->doneList->setContextMenuPolicy(Qt::CustomContextMenu);
    
    // Load data after UI is fully set up
    board->loadFromFile(fileName);

    for (const Task &task : board->getTasks()) {
        addTaskToUI(task);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    board->releaseLock(fileName);
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
    connect(board, &Board::readOnlyMode, this, &MainWindow::onReadOnlyMode);
}

void MainWindow::onReadOnlyMode(bool readOnly){
    ui->todoList->setDragEnabled(!readOnly);
    ui->inProgressList->setDragEnabled(!readOnly);
    ui->doneList->setDragEnabled(!readOnly);
    
    if (readOnly) {
        ui->addBtn->hide();
        if (!reloadBtn) {
            reloadBtn = new QPushButton("Reload", this);
            connect(reloadBtn, &QPushButton::clicked, this, &MainWindow::onReloadClicked);
            reloadBtn->setGeometry(ui->addBtn->geometry());
        }
        reloadBtn->show();
    } else {
        ui->addBtn->show();
        if (reloadBtn) {
            reloadBtn->hide();
        }
    }
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
        item->setData(Qt::UserRole + 1, static_cast<int>(task.priority));
        item->setToolTip(task.description.isEmpty() ? task.title : task.description);
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

        if(list->count() == 0){
            list->addItem(item);
            return;
        }

        bool inserted = false;
        for (int i = 0; i < list->count(); ++i) {
            auto *existingItem = list->item(i);
            int taskPriority = static_cast<int>(task.priority);
            int existingPriority = existingItem->data(Qt::UserRole + 1).toInt();

            if (taskPriority > existingPriority) {
                list->insertItem(i, item);
                inserted = true;
                break;
            }
        }

        if (!inserted) {
            list->addItem(item);
        }
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
        Priority priority = form.getPriority();
        Task task(title, description, Status::ToDo, priority);
        board->addTask(task);
    }
}

void MainWindow::onTaskDropped(const QUuid &id, Status newStatus){
    Task *task = board->getTaskById(id);
    if (task && task->status != newStatus) {
        task->status = newStatus;
        
        // Only reorder tasks in the destination list to maintain priority ordering
        KanbanListWidget *destinationList = nullptr;
        switch (newStatus) {
            case Status::ToDo: destinationList = ui->todoList; break;
            case Status::InProgress: destinationList = ui->inProgressList; break;
            case Status::Done: destinationList = ui->doneList; break;
        }
        
        if (destinationList) {
            // Clear and reload only the destination list
            destinationList->clear();
            for (const Task &taskItem : board->getTasks()) {
                if (taskItem.status == newStatus) {
                    addTaskToUI(taskItem);
                }
            }
        }
        
        board->saveToFile(fileName);
    }
}

void MainWindow::showContextMenu(const QPoint &pos)
{
    if(board->isLocked)
        return;
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
            newTask.id = task->id;
            newTask.createdAt = task->createdAt;
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

void MainWindow::onReloadClicked()
{
    if (board->tryReload(fileName)) {
        ui->todoList->clear();
        ui->inProgressList->clear();
        ui->doneList->clear();
        
        for (const Task &task : board->getTasks()) {
            addTaskToUI(task);
        }
        
        if (board->isLocked) {
            QMessageBox::information(this, "Reload", "Data reloaded successfully. File is still locked by another instance.");
        } else {
            QMessageBox::information(this, "Reload", "Data reloaded successfully. File lock acquired - you can now edit tasks.");
        }
    } else {
        QMessageBox::warning(this, "Reload Error", "Failed to reload data from file. Please check if the file exists and is accessible.");
    }
}
