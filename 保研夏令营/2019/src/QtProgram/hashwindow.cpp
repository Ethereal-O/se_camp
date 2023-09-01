#include "hashwindow.h"
#include "ui_hashwindow.h"

HashWindow::HashWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::HashWindow)
{
    ui->setupUi(this);
}

HashWindow::~HashWindow()
{
    delete ui;
}

