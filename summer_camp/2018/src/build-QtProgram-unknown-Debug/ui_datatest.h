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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_DataTest
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QCustomPlot *direct_1;
    QCustomPlot *direct_2;
    QCustomPlot *direct_3;
    QCustomPlot *direct_4;
    QHBoxLayout *horizontalLayout_3;
    QCustomPlot *symmetry_1;
    QCustomPlot *symmetry_2;
    QCustomPlot *symmetry_3;
    QCustomPlot *symmetry_4;
    QLabel *checkRes;

    void setupUi(QMainWindow *DataTest)
    {
        if (DataTest->objectName().isEmpty())
            DataTest->setObjectName(QString::fromUtf8("DataTest"));
        DataTest->resize(800, 466);
        centralwidget = new QWidget(DataTest);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        direct_1 = new QCustomPlot(centralwidget);
        direct_1->setObjectName(QString::fromUtf8("direct_1"));

        horizontalLayout_2->addWidget(direct_1);

        direct_2 = new QCustomPlot(centralwidget);
        direct_2->setObjectName(QString::fromUtf8("direct_2"));

        horizontalLayout_2->addWidget(direct_2);

        direct_3 = new QCustomPlot(centralwidget);
        direct_3->setObjectName(QString::fromUtf8("direct_3"));

        horizontalLayout_2->addWidget(direct_3);

        direct_4 = new QCustomPlot(centralwidget);
        direct_4->setObjectName(QString::fromUtf8("direct_4"));

        horizontalLayout_2->addWidget(direct_4);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        symmetry_1 = new QCustomPlot(centralwidget);
        symmetry_1->setObjectName(QString::fromUtf8("symmetry_1"));

        horizontalLayout_3->addWidget(symmetry_1);

        symmetry_2 = new QCustomPlot(centralwidget);
        symmetry_2->setObjectName(QString::fromUtf8("symmetry_2"));

        horizontalLayout_3->addWidget(symmetry_2);

        symmetry_3 = new QCustomPlot(centralwidget);
        symmetry_3->setObjectName(QString::fromUtf8("symmetry_3"));

        horizontalLayout_3->addWidget(symmetry_3);

        symmetry_4 = new QCustomPlot(centralwidget);
        symmetry_4->setObjectName(QString::fromUtf8("symmetry_4"));

        horizontalLayout_3->addWidget(symmetry_4);


        verticalLayout->addLayout(horizontalLayout_3);

        checkRes = new QLabel(centralwidget);
        checkRes->setObjectName(QString::fromUtf8("checkRes"));
        checkRes->setMaximumSize(QSize(16777215, 30));

        verticalLayout->addWidget(checkRes);

        DataTest->setCentralWidget(centralwidget);

        retranslateUi(DataTest);

        QMetaObject::connectSlotsByName(DataTest);
    } // setupUi

    void retranslateUi(QMainWindow *DataTest)
    {
        DataTest->setWindowTitle(QApplication::translate("DataTest", "DataTest", nullptr));
        checkRes->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class DataTest: public Ui_DataTest {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATATEST_H
