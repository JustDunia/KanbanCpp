#include "board.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QIODevice>
#include <QDir>

Board::Board(QObject *parent)
    : QObject{parent}
{}

void Board::addTask(Task task) {
    tasks.append(std::move(task));
    emit taskAdded(tasks.last());
}

void Board::removeTask(const QUuid &id) {
    for (int i = 0; i < tasks.size(); ++i) {
        if (tasks[i].id == id) {
            tasks.removeAt(i);
            emit taskRemoved(id);
            break;
        }
    }
}

Task* Board::getTaskById(const QUuid &id) {
    for (Task &t : tasks)
        if (t.id == id)
            return &t;
    return nullptr;
}

QVector<Task> Board::getTasksByStatus(Status status) const {
    QVector<Task> result;
    for (const Task &t : tasks)
        if (t.status == status)
            result.append(t);
    return result;
}

const QVector<Task>& Board::getTasks() const {
    return tasks;
}


bool Board::loadFromFile(const QString &filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly))
        return false;
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    // qDebug() << "Current dir:" << doc.
    if (!doc.isArray())
        return false;
    tasks.clear();
    QJsonArray arr = doc.array();
    for (const auto &v : arr)
        tasks.append(Task::fromJson(v.toObject()));
    emit taskAdded(tasks.last());
    return true;
}

bool Board::saveToFile(const QString &filename) const {
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly))
        return false;
    QJsonArray arr;
    for (const Task &t : tasks)
        arr.append(t.toJson());
    QJsonDocument doc(arr);
    file.write(doc.toJson());
    return true;
}
