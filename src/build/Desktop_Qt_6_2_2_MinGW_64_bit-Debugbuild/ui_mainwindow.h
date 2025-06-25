/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "kanbanlistwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    KanbanListWidget *todoList;
    KanbanListWidget *inProgressList;
    KanbanListWidget *doneList;
    QPushButton *addBtn;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QLabel *label_2;
    QLabel *label;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 110, 771, 431));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(15);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        todoList = new KanbanListWidget(horizontalLayoutWidget);
        todoList->setObjectName(QString::fromUtf8("todoList"));
        todoList->setStyleSheet(QString::fromUtf8("KanbanListWidget::item {\n"
"    background-color: rgb(170, 255, 255);\n"
"    color: black;    \n"
"	border-radius: 10px;\n"
"    padding: 5px;\n"
"}\n"
"\n"
"KanbanListWidget::item:focus {\n"
"    outline: none;\n"
"}\n"
""));
        todoList->setFrameShape(QFrame::Shape::NoFrame);
        todoList->setFrameShadow(QFrame::Shadow::Raised);
        todoList->setSpacing(5);

        horizontalLayout->addWidget(todoList);

        inProgressList = new KanbanListWidget(horizontalLayoutWidget);
        inProgressList->setObjectName(QString::fromUtf8("inProgressList"));
        inProgressList->setStyleSheet(QString::fromUtf8("KanbanListWidget::item {\n"
"    background-color: rgb(255, 255, 127);\n"
"    color: black;    \n"
"	border-radius: 10px;\n"
"    padding: 5px;\n"
"}\n"
""));
        inProgressList->setFrameShape(QFrame::Shape::NoFrame);
        inProgressList->setFrameShadow(QFrame::Shadow::Raised);
        inProgressList->setSpacing(5);

        horizontalLayout->addWidget(inProgressList);

        doneList = new KanbanListWidget(horizontalLayoutWidget);
        doneList->setObjectName(QString::fromUtf8("doneList"));
        doneList->setStyleSheet(QString::fromUtf8("KanbanListWidget::item {\n"
"    background-color: rgb(170, 255, 127);\n"
"    color: black;    \n"
"	border-radius: 10px;\n"
"    padding: 5px;\n"
"}\n"
"\n"
""));
        doneList->setFrameShape(QFrame::Shape::NoFrame);
        doneList->setFrameShadow(QFrame::Shadow::Raised);
        doneList->setSpacing(5);

        horizontalLayout->addWidget(doneList);

        addBtn = new QPushButton(centralwidget);
        addBtn->setObjectName(QString::fromUtf8("addBtn"));
        addBtn->setGeometry(QRect(10, 10, 90, 29));
        addBtn->setStyleSheet(QString::fromUtf8(""));
        horizontalLayoutWidget_2 = new QWidget(centralwidget);
        horizontalLayoutWidget_2->setObjectName(QString::fromUtf8("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(10, 50, 771, 51));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(horizontalLayoutWidget_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setStyleSheet(QString::fromUtf8("font: 700 12pt \"Segoe Script\";\n"
"color: rgb(0, 0, 94);"));
        label_3->setTextFormat(Qt::TextFormat::PlainText);
        label_3->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_2->addWidget(label_3);

        label_2 = new QLabel(horizontalLayoutWidget_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setStyleSheet(QString::fromUtf8("font: 700 12pt \"Segoe Script\";\n"
"color: rgb(0, 0, 94);"));
        label_2->setTextFormat(Qt::TextFormat::PlainText);
        label_2->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_2->addWidget(label_2);

        label = new QLabel(horizontalLayoutWidget_2);
        label->setObjectName(QString::fromUtf8("label"));
        label->setStyleSheet(QString::fromUtf8("font: 700 12pt \"Segoe Script\";\n"
"color: rgb(0, 0, 94);"));
        label->setTextFormat(Qt::TextFormat::PlainText);
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_2->addWidget(label);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        addBtn->setText(QCoreApplication::translate("MainWindow", "New task", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "To do", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "In Progress", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Done", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
