/********************************************************************************
** Form generated from reading UI file 'datatest.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATATEST_H
#define UI_DATATEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DataTest
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *DataTest)
    {
        if (DataTest->objectName().isEmpty())
            DataTest->setObjectName(QString::fromUtf8("DataTest"));
        DataTest->resize(800, 600);
        centralwidget = new QWidget(DataTest);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        DataTest->setCentralWidget(centralwidget);
        menubar = new QMenuBar(DataTest);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        DataTest->setMenuBar(menubar);
        statusbar = new QStatusBar(DataTest);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        DataTest->setStatusBar(statusbar);

        retranslateUi(DataTest);

        QMetaObject::connectSlotsByName(DataTest);
    } // setupUi

    void retranslateUi(QMainWindow *DataTest)
    {
        DataTest->setWindowTitle(QApplication::translate("DataTest", "DataTest", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DataTest: public Ui_DataTest {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATATEST_H
