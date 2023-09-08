/********************************************************************************
** Form generated from reading UI file 'waterwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WATERWINDOW_H
#define UI_WATERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WaterWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *loadFileBtn;
    QPushButton *lastTimeBtn;
    QPushButton *nextTimeBtn;
    QLabel *timeShower;
    QWidget *waterShower;

    void setupUi(QMainWindow *WaterWindow)
    {
        if (WaterWindow->objectName().isEmpty())
            WaterWindow->setObjectName(QString::fromUtf8("WaterWindow"));
        WaterWindow->resize(800, 600);
        centralwidget = new QWidget(WaterWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        loadFileBtn = new QPushButton(centralwidget);
        loadFileBtn->setObjectName(QString::fromUtf8("loadFileBtn"));

        horizontalLayout->addWidget(loadFileBtn);

        lastTimeBtn = new QPushButton(centralwidget);
        lastTimeBtn->setObjectName(QString::fromUtf8("lastTimeBtn"));

        horizontalLayout->addWidget(lastTimeBtn);

        nextTimeBtn = new QPushButton(centralwidget);
        nextTimeBtn->setObjectName(QString::fromUtf8("nextTimeBtn"));

        horizontalLayout->addWidget(nextTimeBtn);

        timeShower = new QLabel(centralwidget);
        timeShower->setObjectName(QString::fromUtf8("timeShower"));

        horizontalLayout->addWidget(timeShower);


        verticalLayout->addLayout(horizontalLayout);

        waterShower = new QWidget(centralwidget);
        waterShower->setObjectName(QString::fromUtf8("waterShower"));

        verticalLayout->addWidget(waterShower);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(1, 10);
        WaterWindow->setCentralWidget(centralwidget);

        retranslateUi(WaterWindow);

        QMetaObject::connectSlotsByName(WaterWindow);
    } // setupUi

    void retranslateUi(QMainWindow *WaterWindow)
    {
        WaterWindow->setWindowTitle(QCoreApplication::translate("WaterWindow", "WaterWindow", nullptr));
        loadFileBtn->setText(QCoreApplication::translate("WaterWindow", "\345\212\240\350\275\275\346\226\207\344\273\266", nullptr));
        lastTimeBtn->setText(QCoreApplication::translate("WaterWindow", "\344\270\212\344\270\200\346\227\266\345\210\273", nullptr));
        nextTimeBtn->setText(QCoreApplication::translate("WaterWindow", "\344\270\213\344\270\200\346\227\266\345\210\273", nullptr));
        timeShower->setText(QCoreApplication::translate("WaterWindow", "\345\275\223\345\211\215\346\227\266\345\210\273\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WaterWindow: public Ui_WaterWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WATERWINDOW_H
