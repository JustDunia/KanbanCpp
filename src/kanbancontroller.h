#pragma once

#ifndef KANBANCONTROLLER_H
#define KANBANCONTROLLER_H
#include "task.h"
#include <QObject>

class KanbanController : public QObject
{
    Q_OBJECT
public:
    explicit KanbanController(QObject *parent = nullptr);

    void addTask(Task task);
    void removeTask(const QUuid &id);
    void updateTask(Task *currentTask, Task newTask);
    Task* getTaskById(const QUuid &id);
    const QVector<Task>& getTasks() const;
    bool loadFromFile(const QString &filename);
    bool saveToFile(const QString &filename) const;
    void sortTasksByPriority();
    void releaseLock(const QString &filename);
    bool tryReload(const QString &filename);

    bool isLocked;

signals:
    void taskAdded(const Task &task);
    void taskRemoved(const QUuid &id);
    void taskUpdated(const Task &task);
    void readOnlyMode(bool readOnly);

private:
    QVector<Task> tasks;
};

#endif // KANBANCONTROLLER_H
