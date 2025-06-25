#pragma once

#ifndef KANBANCONTROLLER_H
#define KANBANCONTROLLER_H
#include "task.h"
#include <QObject>
#include <QString>

class KanbanController : public QObject
{
    Q_OBJECT
public:
    explicit KanbanController(QObject *parent = nullptr);

    void setFileName(const QString &filename);
    void addTask(Task task);
    void removeTask(const QUuid &id);
    void updateTask(Task *currentTask, Task newTask);
    void updateTaskStatus(const QUuid &id, Status newStatus);
    Task* getTaskById(const QUuid &id);
    const QVector<Task>& getTasks() const;
    bool loadFromFile();
    bool saveToFile() const;
    void sortTasksByPriority();
    void releaseLock();
    bool tryReload();

    bool isLocked;

signals:
    void taskAdded(const Task &task);
    void taskRemoved(const QUuid &id);
    void taskUpdated(const Task &task);
    void readOnlyMode(bool readOnly);

private:
    QVector<Task> tasks;
    QString fileName;
};

#endif // KANBANCONTROLLER_H
