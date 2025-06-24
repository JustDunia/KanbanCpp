#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "boardwidget.h"
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

private:
    Ui::MainWindow *ui;
    Board *board;
    BoardWidget *boardWidget;
};
#endif // MAINWINDOW_H
