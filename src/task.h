#ifndef TASK_H
#define TASK_H
#include <QString>
#include <QJsonObject>
#include "status.h"

class Task
{
public:
    Task(QString t = "", Status s = Status::ToDo);

    QUuid id;
    QString title;
    Status status;

    QJsonObject toJson() const;
    static Task fromJson(const QJsonObject &obj);
};

#endif // TASK_H
