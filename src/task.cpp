#include "task.h"

Task::Task(QString t, QString d, Status s) :
    id(QUuid::createUuid()),
    title(std::move(t)),
    description(d),
    status(s)
{
}

QJsonObject Task::toJson() const
{
    QJsonObject obj;
    obj["id"] = id.toString();
    obj["title"] = title;
    obj["description"] = description;
    obj["status"] = static_cast<int>(status);
    return obj;
}

Task Task::fromJson(const QJsonObject &obj)
{
    Task task;
    task.id = QUuid(obj["id"].toString());
    task.title = obj["title"].toString();
    task.description = obj["description"].toString();
    task.status = static_cast<Status>(obj["status"].toInt());
    return task;
}
