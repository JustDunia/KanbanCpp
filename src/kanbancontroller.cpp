#include "kanbancontroller.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QIODevice>
#include <QMessageBox>
#include <algorithm>

KanbanController::KanbanController(QObject *parent)
    : QObject{parent}, isLocked(false), fileName("kanban.json")
{}

void KanbanController::setFileName(const QString &filename) {
    fileName = filename;
}

void KanbanController::addTask(Task task) {
    tasks.append(std::move(task));
    emit taskAdded(tasks.last());
    saveToFile();
}

void KanbanController::removeTask(const QUuid &id) {
    for (int i = 0; i < tasks.size(); ++i) {
        if (tasks[i].id == id) {
            tasks.removeAt(i);
            emit taskRemoved(id);
            saveToFile();
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
        saveToFile();
    }
}

Task* KanbanController::getTaskById(const QUuid &id) {
    for (Task &t : tasks)
        if (t.id == id)
            return &t;
    return nullptr;
}

void KanbanController::updateTaskStatus(const QUuid &id, Status newStatus) {
    Task *task = getTaskById(id);
    if (task && task->status != newStatus) {
        task->status = newStatus;
        saveToFile();
    }
}

const QVector<Task>& KanbanController::getTasks() const {
    return tasks;
}


bool KanbanController::loadFromFile() {
    QString lockFilePath = fileName + ".lock";
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

    QFile file(fileName);
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

void KanbanController::releaseLock() {
    if(isLocked)
        return;
    QString lockFilePath = fileName + ".lock";
    QFile lockFile(lockFilePath);
    if (lockFile.exists()) {
        lockFile.remove();
    }
}

bool KanbanController::saveToFile() const {
    if (isLocked) {
        return false; // Cannot save if file is locked
    }
    
    QFile file(fileName);
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

bool KanbanController::tryReload() {
    QString lockFilePath = fileName + ".lock";
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

    QFile file(fileName);
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
