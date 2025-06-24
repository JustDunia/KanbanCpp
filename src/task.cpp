#include "task.h"

Task::Task(QString t, Status s) :
    id(QUuid::createUuid()),
    title(std::move(t)),
    status(s)
{
}

QJsonObject Task::toJson() const
{
    QJsonObject obj;
    obj["id"] = id.toString();
    obj["title"] = title;
    obj["status"] = static_cast<int>(status);
    return obj;
}

Task Task::fromJson(const QJsonObject &obj)
{
    Task task;
    task.id = QUuid(obj["id"].toString());
    task.title = obj["title"].toString();
    task.status = static_cast<Status>(obj["status"].toInt());
    return task;
}
