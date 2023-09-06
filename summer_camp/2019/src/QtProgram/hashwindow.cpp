#include "hashwindow.h"
#include "ui_hashwindow.h"
#include "hash.h"
#include <QFileDialog>
#include <QDebug>

HashWindow::HashWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::HashWindow)
{
    ui->setupUi(this);
    connect(ui->selectBtn,&QPushButton::clicked,this,&HashWindow::selectFile);
    connect(ui->fileInput,&QLineEdit::textChanged,this,&HashWindow::inputFile);
    connect(ui->confirmBtn,&QPushButton::clicked,this,&HashWindow::confirm);
}

HashWindow::~HashWindow()
{
    delete ui;
}

void HashWindow::selectFile()
{
    QFileDialog f(this);
    f.setWindowTitle("选择文件");
    f.setViewMode(QFileDialog::Detail);

    if(f.exec()==QDialog::Accepted)
        filePath=f.selectedFiles()[0];

    ui->fileInput->setText(filePath);
}

void HashWindow::inputFile()
{
    filePath=ui->fileInput->text();
}

void HashWindow::confirm()
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
    QString content = proceed(v);
    QFile file_2("ans.txt");
    if (!file_2.open(QIODevice::WriteOnly|QIODevice::Text))
        return;
    file_2.write(content.toUtf8().data());
}

QString HashWindow::proceed(QVector<QString>& options)
{
    QString res;

    //    Hash *aa = new CuckooHash(std::make_unique<CaculateHashNormal>());
        Hash *aa = new LinearHash(std::make_unique<CaculateHashNormal>());

        if (aa->GetType()==HASHTYPE::CUCKOOHASH)
            qDebug()<<"CUCKOOHASH";
        else if (aa->GetType()==HASHTYPE::LINEARHASH)
            qDebug()<<"LINEARHASH";

    std::string option;
    int32_t k;
    int32_t v;
    for (auto&& a:options)
    {
        auto m=std::stringstream(a.toUtf8().data());
        m>>option>>k>>v;
        if (option.compare("Set")==0)
        {
            aa->Set(k,v);
        }
        if (option.compare("Get")==0)
        {
            auto pair=aa->Get(k);
            if (pair.has_value())
                res+=QString::number(pair.value().second)+"\n";
            else
                res+="null\n";
        }
        if (option.compare("Del")==0)
        {
            aa->Delete(k);
        }
    }
    return res;
}
