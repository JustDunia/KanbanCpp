#include "mainwindow.h"
#include "createform.h"
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
}

void MainWindow::addTaskToUI(const Task &task) {
    QListWidget *list = nullptr;
    switch (task.status) {
    case Status::ToDo: list = ui->todoList; break;
    case Status::InProgress: list = ui->inProgressList; break;
    case Status::Done: list = ui->doneList; break;
    }
    if (list) {
        QListWidgetItem *item = new QListWidgetItem(task.title);
        item->setData(Qt::UserRole, task.id);
        list->addItem(item);
    }
}

void MainWindow::onTaskAdded(const Task &task) {
    addTaskToUI(task);
    board->saveToFile(fileName);
}

void MainWindow::onTaskUpdated(const Task &task) {
    QList<QListWidget*> lists = { ui->todoList, ui->inProgressList, ui->doneList };
    for (QListWidget *list : lists) {
        for (int i = 0; i < list->count(); ++i) {
            auto *item = list->item(i);
            if (item->data(Qt::UserRole).toUuid() == task.id) {
                list->takeItem(i);
                delete item;
                addTaskToUI(task);
                return;
            }
        }
    }
}

void MainWindow::onTaskRemoved(const QUuid &id) {
    QList<QListWidget*> lists = { ui->todoList, ui->inProgressList, ui->doneList };
    for (QListWidget *list : lists) {
        for (int i = 0; i < list->count(); ++i) {
            auto *item = list->item(i);
            if (item->data(Qt::UserRole).toUuid() == id) {
                delete list->takeItem(i);
                return;
            }
        }
    }
}

void MainWindow::on_addBtn_clicked()
{
    CreateForm form(this);
    form.setWindowTitle("New task");
    if (form.exec() == QDialog::Accepted) {
        QString title = form.getTitle();
        QString description = form.getDescription();
        Task task(title, description);
        board->addTask(task);
    }
}

