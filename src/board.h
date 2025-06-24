#ifndef BOARD_H
#define BOARD_H
#include "task.h"
#include "status.h"
#include <QWidget>

namespace Ui {
class Board;
}

class Board : public QWidget
{
    Q_OBJECT

public:
    explicit Board(QWidget *parent = nullptr);
    ~Board();

    QVector<Task> tasks;

    void addTask(const Task &task);
    void updateTask(const QUuid &id, const Task &task);
    void removeTask(const QUuid &id);
    Task* getTaskById(const QUuid &id);
    QVector<Task> getTasksByStatus(Status status) const;
    bool saveToFile(const QString &filename) const;
    bool loadFromFile(const QString &filename);

private:
    Ui::Board *ui;

signals:
    void boardChanged();
};

#endif // BOARD_H
