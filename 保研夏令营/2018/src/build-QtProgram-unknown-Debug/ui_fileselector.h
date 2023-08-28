/********************************************************************************
** Form generated from reading UI file 'fileselector.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILESELECTOR_H
#define UI_FILESELECTOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FileSelector
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QPushButton *selectBtn;
    QLineEdit *fileInput;
    QPushButton *confirmBtn;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QMainWindow *FileSelector)
    {
        if (FileSelector->objectName().isEmpty())
            FileSelector->setObjectName(QString::fromUtf8("FileSelector"));
        FileSelector->resize(800, 600);
        centralwidget = new QWidget(FileSelector);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

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

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        FileSelector->setCentralWidget(centralwidget);

        retranslateUi(FileSelector);

        QMetaObject::connectSlotsByName(FileSelector);
    } // setupUi

    void retranslateUi(QMainWindow *FileSelector)
    {
        FileSelector->setWindowTitle(QApplication::translate("FileSelector", "MainWindow", nullptr));
        selectBtn->setText(QApplication::translate("FileSelector", "\351\200\211\346\213\251", nullptr));
        fileInput->setInputMask(QString());
        fileInput->setText(QString());
        confirmBtn->setText(QApplication::translate("FileSelector", "\347\241\256\350\256\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FileSelector: public Ui_FileSelector {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILESELECTOR_H
