#include "hashwindow.h"
#include "ui_hashwindow.h"
#include <QDebug>
#include "hash.h"

HashWindow::HashWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::HashWindow)
{
    ui->setupUi(this);
    CuckooHash *aa = new CuckooHash(std::make_unique<CaculateHashNormal>());

    for (int i = 0; i < 1600; i++)
    {
        aa->Set(i, i + 1);
    }
    for (int i = 0; i < 1600; i++)
    {
        assert(aa->Get(i).value().second == i + 1);
    }
    for (int i = 0; i < 1600; i++)
    {
        aa->Delete(i);
    }
    for (int i = 0; i < 1800; i++)
    {
        assert(!aa->Get(i).has_value());
    }
    qDebug() << "finished";
}

HashWindow::~HashWindow()
{
    delete ui;
}
