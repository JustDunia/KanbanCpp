#include "boardwidget.h"
#include "ui_boardwidget.h"

BoardWidget::BoardWidget(Board *board, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::BoardWidget)
    , board(board)
{
    ui->setupUi(this);
    connectSignals();
    for (const Task &task : board->getTasks()) {
        addTaskToUI(task);
    }
}

BoardWidget::~BoardWidget()
{
    delete ui;
}

void BoardWidget::connectSignals() {
    connect(board, &Board::taskAdded, this, &BoardWidget::onTaskAdded);
    connect(board, &Board::taskUpdated, this, &BoardWidget::onTaskUpdated);
    connect(board, &Board::taskRemoved, this, &BoardWidget::onTaskRemoved);
}

void BoardWidget::addTaskToUI(const Task &task) {
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

void BoardWidget::onTaskAdded(const Task &task) {
    addTaskToUI(task);
}

void BoardWidget::onTaskUpdated(const Task &task) {
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

void BoardWidget::onTaskRemoved(const QUuid &id) {
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
