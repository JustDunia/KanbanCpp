#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "board.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onTaskAdded(const Task &task);
    void onTaskRemoved(const QUuid &id);
    void onTaskUpdated(const Task &task);
    void onTaskMoved();

    void on_addBtn_clicked();

private:
    Ui::MainWindow *ui;
    Board *board;
    QString fileName;

    void connectSignals();
    void addTaskToUI(const Task &task);
    void onTaskDropped(const QUuid &id, Status newStatus);
    void showContextMenu(const QPoint &pos);
};
#endif // MAINWINDOW_H
