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
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HashWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QPushButton *selectBtn;
    QLineEdit *fileInput;
    QPushButton *confirmBtn;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QMainWindow *HashWindow)
    {
        if (HashWindow->objectName().isEmpty())
            HashWindow->setObjectName(QString::fromUtf8("HashWindow"));
        HashWindow->resize(800, 600);
        centralwidget = new QWidget(HashWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalSpacer = new QSpacerItem(20, 243, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        selectBtn = new QPushButton(centralwidget);
        selectBtn->setObjectName(QString::fromUtf8("selectBtn"));

        verticalLayout->addWidget(selectBtn);

        fileInput = new QLineEdit(centralwidget);
        fileInput->setObjectName(QString::fromUtf8("fileInput"));

        verticalLayout->addWidget(fileInput);

        confirmBtn = new QPushButton(centralwidget);
        confirmBtn->setObjectName(QString::fromUtf8("confirmBtn"));

        verticalLayout->addWidget(confirmBtn);

        verticalSpacer_2 = new QSpacerItem(20, 243, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        HashWindow->setCentralWidget(centralwidget);

        retranslateUi(HashWindow);

        QMetaObject::connectSlotsByName(HashWindow);
    } // setupUi

    void retranslateUi(QMainWindow *HashWindow)
    {
        HashWindow->setWindowTitle(QCoreApplication::translate("HashWindow", "HashWindow", nullptr));
        selectBtn->setText(QCoreApplication::translate("HashWindow", "\351\200\211\346\213\251", nullptr));
        fileInput->setInputMask(QString());
        fileInput->setText(QString());
        confirmBtn->setText(QCoreApplication::translate("HashWindow", "\347\241\256\350\256\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HashWindow: public Ui_HashWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HASHWINDOW_H
