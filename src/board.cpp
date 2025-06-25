#include "board.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QIODevice>
#include <QLockFile>
#include <QMessageBox>

Board::Board(QObject *parent)
    : QObject{parent}
{}

void Board::addTask(Task task) {
    tasks.append(std::move(task));
    emit taskAdded(tasks.last());
}

void Board::removeTask(const QUuid &id) {
    for (int i = 0; i < tasks.size(); ++i) {
        if (tasks[i].id == id) {
            tasks.removeAt(i);
            emit taskRemoved(id);
            break;
        }
    }
}

void Board::updateTask(Task *currentTask, Task newTask){
    if(currentTask && !newTask.title.isEmpty() && (currentTask->title != newTask.title || currentTask->description != newTask.description || currentTask->priority != newTask.priority) ){
        currentTask->title = newTask.title;
        currentTask->description = newTask.description;
        currentTask->priority = newTask.priority;
        newTask.id = currentTask->id;
        emit taskUpdated(newTask);
    }
}

Task* Board::getTaskById(const QUuid &id) {
    for (Task &t : tasks)
        if (t.id == id)
            return &t;
    return nullptr;
}

const QVector<Task>& Board::getTasks() const {
    return tasks;
}


bool Board::loadFromFile(const QString &filename) {
    QString lockFilePath = filename + ".lock";
    QFile lockFile(lockFilePath);

    isLocked = false;
    if (lockFile.exists()) {
        QMessageBox::warning(nullptr, "Plik zablokowany", "Inna instancja aplikacji edytuje plik.");
        isLocked = true;
    }

    if (!lockFile.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(nullptr, "Błąd blokady", "Nie udało się utworzyć pliku blokady.");
        return false;
    }

    lockFile.close();

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(nullptr, "Błąd pliku", "Nie udało się otworzyć pliku.");
        return false;
    }

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();

    if (!doc.isArray()) {
        QMessageBox::warning(nullptr, "Błąd formatu", "Plik nie zawiera poprawnych danych.");
        return false;
    }

    tasks.clear();
    QJsonArray arr = doc.array();
    for (const auto &v : arr)
        tasks.append(Task::fromJson(v.toObject()));

    if (tasks.empty()) {
        QMessageBox::warning(nullptr, "Błąd danych", "Plik nie zawiera żadnych zadań.");
        return false;
    }

    emit taskAdded(tasks.last());
    emit readOnlyMode(isLocked);

    return true;
}

void Board::releaseLock(const QString &filename) {
    if(isLocked)
        return;
    QString lockFilePath = filename + ".lock";
    QFile lockFile(lockFilePath);
    if (lockFile.exists()) {
        lockFile.remove();
    }
}

bool Board::saveToFile(const QString &filename) const {
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly))
        return false;
    QJsonArray arr;
    for (const Task &t : tasks)
        arr.append(t.toJson());
    QJsonDocument doc(arr);
    file.write(doc.toJson());
    return true;
}

void Board::sortTasksByPriority()
{
    std::sort(tasks.begin(), tasks.end(), [](const Task& task1, const Task& task2) {
        return task1.priority > task2.priority;
    });
}
