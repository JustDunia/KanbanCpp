#pragma once

#ifndef BOARD_H
#define BOARD_H
#include "task.h"
#include <QObject>

class Board : public QObject
{
    Q_OBJECT
public:
    explicit Board(QObject *parent = nullptr);

    void addTask(Task task);
    void removeTask(const QUuid &id);
    Task* getTaskById(const QUuid &id);
    QVector<Task> getTasksByStatus(Status status) const;
    const QVector<Task>& getTasks() const;


    bool loadFromFile(const QString &filename);
    bool saveToFile(const QString &filename) const;

signals:
    void taskAdded(const Task &task);
    void taskRemoved(const QUuid &id);
    void taskUpdated(const Task &task);

private:
    QVector<Task> tasks;

};

#endif // BOARD_H
