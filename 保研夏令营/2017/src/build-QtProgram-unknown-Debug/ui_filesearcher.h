/********************************************************************************
** Form generated from reading UI file 'filesearcher.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILESEARCHER_H
#define UI_FILESEARCHER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_fileSearcher
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *searcherInput;
    QPushButton *searcherBtn;
    QLabel *label_2;
    QTextBrowser *searcherRes;

    void setupUi(QMainWindow *fileSearcher)
    {
        if (fileSearcher->objectName().isEmpty())
            fileSearcher->setObjectName(QString::fromUtf8("fileSearcher"));
        fileSearcher->resize(800, 600);
        centralwidget = new QWidget(fileSearcher);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        searcherInput = new QLineEdit(centralwidget);
        searcherInput->setObjectName(QString::fromUtf8("searcherInput"));

        horizontalLayout->addWidget(searcherInput);

        searcherBtn = new QPushButton(centralwidget);
        searcherBtn->setObjectName(QString::fromUtf8("searcherBtn"));

        horizontalLayout->addWidget(searcherBtn);


        verticalLayout->addLayout(horizontalLayout);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout->addWidget(label_2);

        searcherRes = new QTextBrowser(centralwidget);
        searcherRes->setObjectName(QString::fromUtf8("searcherRes"));

        verticalLayout->addWidget(searcherRes);

        fileSearcher->setCentralWidget(centralwidget);

        retranslateUi(fileSearcher);

        QMetaObject::connectSlotsByName(fileSearcher);
    } // setupUi

    void retranslateUi(QMainWindow *fileSearcher)
    {
        fileSearcher->setWindowTitle(QApplication::translate("fileSearcher", "MainWindow", nullptr));
        label->setText(QApplication::translate("fileSearcher", "\350\257\267\350\276\223\345\205\245\346\220\234\347\264\242\351\241\271", nullptr));
        searcherBtn->setText(QApplication::translate("fileSearcher", "\347\241\256\350\256\244", nullptr));
        label_2->setText(QApplication::translate("fileSearcher", "\347\273\223\346\236\234", nullptr));
    } // retranslateUi

};

namespace Ui {
    class fileSearcher: public Ui_fileSearcher {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILESEARCHER_H
