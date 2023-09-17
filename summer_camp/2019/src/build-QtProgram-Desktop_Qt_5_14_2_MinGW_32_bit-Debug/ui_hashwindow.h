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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HashWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *keyEdit;
    QLabel *label_2;
    QLineEdit *valueEdit;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *insertButton;
    QPushButton *deleteButton;
    QHBoxLayout *horizontalLayout_2;
    QWidget *hashTableWidget_1;
    QWidget *hashTableWidget_2;

    void setupUi(QMainWindow *HashWindow)
    {
        if (HashWindow->objectName().isEmpty())
            HashWindow->setObjectName(QString::fromUtf8("HashWindow"));
        HashWindow->resize(800, 600);
        centralwidget = new QWidget(HashWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMaximumSize(QSize(16777215, 30));

        horizontalLayout->addWidget(label);

        keyEdit = new QLineEdit(centralwidget);
        keyEdit->setObjectName(QString::fromUtf8("keyEdit"));
        keyEdit->setMaximumSize(QSize(16777215, 30));

        horizontalLayout->addWidget(keyEdit);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMaximumSize(QSize(16777215, 30));

        horizontalLayout->addWidget(label_2);

        valueEdit = new QLineEdit(centralwidget);
        valueEdit->setObjectName(QString::fromUtf8("valueEdit"));
        valueEdit->setMaximumSize(QSize(16777215, 30));

        horizontalLayout->addWidget(valueEdit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        insertButton = new QPushButton(centralwidget);
        insertButton->setObjectName(QString::fromUtf8("insertButton"));
        insertButton->setMaximumSize(QSize(16777215, 30));

        horizontalLayout_3->addWidget(insertButton);

        deleteButton = new QPushButton(centralwidget);
        deleteButton->setObjectName(QString::fromUtf8("deleteButton"));
        deleteButton->setMaximumSize(QSize(16777215, 30));

        horizontalLayout_3->addWidget(deleteButton);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        hashTableWidget_1 = new QWidget(centralwidget);
        hashTableWidget_1->setObjectName(QString::fromUtf8("hashTableWidget_1"));

        horizontalLayout_2->addWidget(hashTableWidget_1);

        hashTableWidget_2 = new QWidget(centralwidget);
        hashTableWidget_2->setObjectName(QString::fromUtf8("hashTableWidget_2"));

        horizontalLayout_2->addWidget(hashTableWidget_2);


        verticalLayout->addLayout(horizontalLayout_2);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(1, 1);
        verticalLayout->setStretch(2, 10);
        HashWindow->setCentralWidget(centralwidget);

        retranslateUi(HashWindow);

        QMetaObject::connectSlotsByName(HashWindow);
    } // setupUi

    void retranslateUi(QMainWindow *HashWindow)
    {
        HashWindow->setWindowTitle(QCoreApplication::translate("HashWindow", "HashWindow", nullptr));
        label->setText(QCoreApplication::translate("HashWindow", "\351\224\256", nullptr));
        label_2->setText(QCoreApplication::translate("HashWindow", "\345\200\274", nullptr));
        insertButton->setText(QCoreApplication::translate("HashWindow", "\346\217\222\345\205\245", nullptr));
        deleteButton->setText(QCoreApplication::translate("HashWindow", "\345\210\240\351\231\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HashWindow: public Ui_HashWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HASHWINDOW_H
