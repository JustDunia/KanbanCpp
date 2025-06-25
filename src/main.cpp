#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString globalStyle = R"(
        /* === QPushButton === */
        QPushButton {
            background-color: #3498db;
            color: white;
            border: none;
            border-radius: 6px;
            padding: 8px 16px;
            font-size: 14px;
        }

        QPushButton:hover {
            background-color: #5dade2;
        }

        QPushButton:pressed {
            background-color: #2e86c1;
        }

        QPushButton:disabled {
            background-color: #bdc3c7;
            color: #ecf0f1;
        }


        /* === QLineEdit === */
        QLineEdit {
            background-color: #ffffff;
            color: #2c3e50;
            border: 1px solid #ccc;
            border-radius: 4px;
            padding: 6px 8px;
            font-size: 14px;
        }

        QLineEdit:focus {
            border: 1px solid #3498db;
            background-color: #f0faff;
        }


        /* === QPlainTextEdit === */
        QPlainTextEdit {
            background-color: #ffffff;
            color: #2c3e50;
            border: 1px solid #ccc;
            border-radius: 4px;
            padding: 6px;
            font-size: 14px;
            font-family: Consolas, Courier, monospace;
        }

        QPlainTextEdit:focus {
            border: 1px solid #3498db;
            background-color: #f0faff;
        }
    )";

    a.setStyleSheet(globalStyle);
    MainWindow w;
    w.show();
    return a.exec();
}
