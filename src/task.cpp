#include "task.h"
#include "priority.h"

Task::Task(QString t, QString d, Status s, Priority p) :
    id(QUuid::createUuid()),
    title(std::move(t)),
    description(d),
    status(s),
    createdAt(QDateTime::currentDateTime()),
    priority(p)
{
}

QJsonObject Task::toJson() const
{
    QJsonObject obj;
    obj["id"] = id.toString();
    obj["title"] = title;
    obj["description"] = description;
    obj["status"] = static_cast<int>(status);
    obj["createdAt"] = createdAt.toString(Qt::ISODate);
    obj["priority"] = static_cast<int>(priority);
    return obj;
}

Task Task::fromJson(const QJsonObject &obj)
{
    Task task;
    task.id = QUuid(obj["id"].toString());
    task.title = obj["title"].toString();
    task.description = obj["description"].toString();
    task.status = static_cast<Status>(obj["status"].toInt());
    task.createdAt = QDateTime::fromString(obj["createdAt"].toString(), Qt::ISODate);
    task.priority = static_cast<Priority>(obj["priority"].toInt());
    return task;
}
