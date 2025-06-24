/********************************************************************************
** Form generated from reading UI file 'boardwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.2.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BOARDWIDGET_H
#define UI_BOARDWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BoardWidget
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QHBoxLayout *horizontalLayout_2;
    QListWidget *todoList;
    QListWidget *inProgressList;
    QListWidget *doneList;

    void setupUi(QWidget *BoardWidget)
    {
        if (BoardWidget->objectName().isEmpty())
            BoardWidget->setObjectName(QString::fromUtf8("BoardWidget"));
        BoardWidget->resize(668, 462);
        horizontalLayoutWidget = new QWidget(BoardWidget);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(0, 0, 661, 461));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        todoList = new QListWidget(horizontalLayoutWidget);
        todoList->setObjectName(QString::fromUtf8("todoList"));

        horizontalLayout_2->addWidget(todoList);

        inProgressList = new QListWidget(horizontalLayoutWidget);
        inProgressList->setObjectName(QString::fromUtf8("inProgressList"));

        horizontalLayout_2->addWidget(inProgressList);

        doneList = new QListWidget(horizontalLayoutWidget);
        doneList->setObjectName(QString::fromUtf8("doneList"));

        horizontalLayout_2->addWidget(doneList);


        horizontalLayout->addLayout(horizontalLayout_2);


        retranslateUi(BoardWidget);

        QMetaObject::connectSlotsByName(BoardWidget);
    } // setupUi

    void retranslateUi(QWidget *BoardWidget)
    {
        BoardWidget->setWindowTitle(QCoreApplication::translate("BoardWidget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BoardWidget: public Ui_BoardWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BOARDWIDGET_H
