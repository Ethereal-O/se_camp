/********************************************************************************
** Form generated from reading UI file 'hashwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HASHWINDOW_H
#define UI_HASHWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HashWindow
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *HashWindow)
    {
        if (HashWindow->objectName().isEmpty())
            HashWindow->setObjectName(QString::fromUtf8("HashWindow"));
        HashWindow->resize(800, 600);
        centralwidget = new QWidget(HashWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        HashWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(HashWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        HashWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(HashWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        HashWindow->setStatusBar(statusbar);

        retranslateUi(HashWindow);

        QMetaObject::connectSlotsByName(HashWindow);
    } // setupUi

    void retranslateUi(QMainWindow *HashWindow)
    {
        HashWindow->setWindowTitle(QCoreApplication::translate("HashWindow", "HashWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HashWindow: public Ui_HashWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HASHWINDOW_H
