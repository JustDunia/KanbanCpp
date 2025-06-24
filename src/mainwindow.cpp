#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "boardwidget.h"
#include <QStandardPaths>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    board = new Board(this);
    board->loadFromFile("kanban.json");

    boardWidget = new BoardWidget(board, this);
    setCentralWidget(boardWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}
