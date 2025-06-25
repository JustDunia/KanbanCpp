#include "kanbancontroller.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QIODevice>
#include <QMessageBox>
#include <algorithm>

KanbanController::KanbanController(QObject *parent)
    : QObject{parent}, isLocked(false)
{}

void KanbanController::addTask(Task task) {
    tasks.append(std::move(task));
    emit taskAdded(tasks.last());
}

void KanbanController::removeTask(const QUuid &id) {
    for (int i = 0; i < tasks.size(); ++i) {
        if (tasks[i].id == id) {
            tasks.removeAt(i);
            emit taskRemoved(id);
            break;
        }
    }
}

void KanbanController::updateTask(Task *currentTask, Task newTask){
    if(currentTask && !newTask.title.isEmpty() && (currentTask->title != newTask.title || currentTask->description != newTask.description || currentTask->priority != newTask.priority) ){
        currentTask->title = newTask.title;
        currentTask->description = newTask.description;
        currentTask->priority = newTask.priority;
        currentTask->status = newTask.status;
        newTask.id = currentTask->id;
        newTask.createdAt = currentTask->createdAt;
        emit taskUpdated(newTask);
    }
}

Task* KanbanController::getTaskById(const QUuid &id) {
    for (Task &t : tasks)
        if (t.id == id)
            return &t;
    return nullptr;
}

const QVector<Task>& KanbanController::getTasks() const {
    return tasks;
}


bool KanbanController::loadFromFile(const QString &filename) {
    QString lockFilePath = filename + ".lock";
    QFile lockFile(lockFilePath);

    isLocked = false;
    if (lockFile.exists()) {
        QMessageBox::warning(nullptr, "File locked", "Different user is editing file");
        isLocked = true;
    }

    if (!isLocked && !lockFile.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(nullptr, "Lock error", "Could not create lock file");
        isLocked = true;
    }

    if (lockFile.isOpen()) {
        lockFile.close();
    }

    QFile file(filename);
    if (!file.exists()) {
        if (file.open(QIODevice::WriteOnly)) {
            file.write("[]");
            file.close();
        }
    }
    
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(nullptr, "File error", "Could not open file");
        return false;
    }

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();

    if (!doc.isArray()) {
        QMessageBox::warning(nullptr, "Format error", "File has invalid data");
        return false;
    }

    tasks.clear();
    QJsonArray arr = doc.array();
    for (const auto &v : arr)
        tasks.append(Task::fromJson(v.toObject()));

    emit readOnlyMode(isLocked);

    return true;
}

void KanbanController::releaseLock(const QString &filename) {
    if(isLocked)
        return;
    QString lockFilePath = filename + ".lock";
    QFile lockFile(lockFilePath);
    if (lockFile.exists()) {
        lockFile.remove();
    }
}

bool KanbanController::saveToFile(const QString &filename) const {
    if (isLocked) {
        return false; // Cannot save if file is locked
    }
    
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly))
        return false;
    QJsonArray arr;
    for (const Task &t : tasks)
        arr.append(t.toJson());
    QJsonDocument doc(arr);
    file.write(doc.toJson());
    file.close();
    return true;
}

void KanbanController::sortTasksByPriority()
{
    std::sort(tasks.begin(), tasks.end(), [](const Task& task1, const Task& task2) {
        return task1.priority > task2.priority;
    });
}

bool KanbanController::tryReload(const QString &filename) {
    QString lockFilePath = filename + ".lock";
    QFile lockFile(lockFilePath);

    if (lockFile.exists()) {
        isLocked = true;
    } else {
        isLocked = false;
        if (!lockFile.open(QIODevice::WriteOnly)) {
            isLocked = true;
        } else {
            lockFile.close();
        }
    }

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    }

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();

    if (!doc.isArray()) {
        return false;
    }

    tasks.clear();
    QJsonArray arr = doc.array();
    for (const auto &v : arr)
        tasks.append(Task::fromJson(v.toObject()));

    emit readOnlyMode(isLocked);
    return true;
}
