#ifndef BOARDWIDGET_H
#define BOARDWIDGET_H
#include "task.h"
#include "board.h"
#include <QWidget>
#include <QListWidget>

namespace Ui {
class BoardWidget;
}

class BoardWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BoardWidget(Board *board, QWidget *parent = nullptr);
    ~BoardWidget();

private slots:
    void onTaskAdded(const Task &task);
    void onTaskRemoved(const QUuid &id);
    void onTaskUpdated(const Task &task);

    void on_pushButton_clicked();

private:
    Ui::BoardWidget *ui;
    Board *board;
    void connectSignals();
    void addTaskToUI(const Task &task);
};

#endif // BOARDWIDGET_H
