#include "fileselector.h"
#include "ui_fileselector.h"
#include "filesearcher.h"
#include <QFileDialog>
#include <QDebug>

FileSelector::FileSelector(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FileSelector)
{
    ui->setupUi(this);
    connect(ui->fileSelectorBtn,&QPushButton::clicked,this,&FileSelector::selectFile);
    connect(ui->confirmBtn,&QPushButton::clicked,this,&FileSelector::confirm);
}

FileSelector::~FileSelector()
{
    delete ui;
}

void FileSelector::selectFile()
{
    QFileDialog f(this);
    f.setWindowTitle("选择文件");
    f.setViewMode(QFileDialog::Detail);

    if(f.exec()==QDialog::Accepted)
        filePath=f.selectedFiles()[0];

    ui->fileSelectorShower->setText(filePath);
}

void FileSelector::confirm()
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        return;
    }
    QTextStream readStream(&file);
    QVector<QString> v;
    while(!readStream.atEnd())
        v.push_back(readStream.readLine());

    fileSearcher *w=new fileSearcher(v);
    w->show();
    this->close();
}
