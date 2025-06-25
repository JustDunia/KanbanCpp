#pragma once

#include "priority.h"
#ifndef TASK_H
#define TASK_H
#include <QString>
#include <QJsonObject>
#include <QUuid>
#include <QDateTime>
#include "status.h"

class Task
{
public:
    Task(QString t = "new task", QString d = "", Status s = Status::ToDo, Priority p = Priority::Low);

    QUuid id;
    QString title;
    QString description;
    Status status;
    QDateTime createdAt;
    Priority priority;

    QJsonObject toJson() const;
    static Task fromJson(const QJsonObject &obj);
};

#endif // TASK_H
