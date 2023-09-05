#include "fileselector.h"
#include "ui_fileselector.h"
#include "datatest.h"
#include <QFileDialog>
#include <QDebug>

FileSelector::FileSelector(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FileSelector)
{
    ui->setupUi(this);

    connect(ui->selectBtn,&QPushButton::clicked,this,&FileSelector::selectFile);
    connect(ui->fileInput,&QLineEdit::textChanged,this,&FileSelector::inputFile);
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

    ui->fileInput->setText(filePath);
}

void FileSelector::inputFile()
{
    filePath=ui->fileInput->text();
}

void FileSelector::confirm()
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly|QIODevice::Text))
        return;
    QTextStream readStream(&file);
    QVector<QString> v;
    while(!readStream.atEnd())
    {
        QString line=readStream.readLine();
        v.push_back(line);
    }

    DataTest *w=new DataTest(v);
    w->show();
    this->close();
}
