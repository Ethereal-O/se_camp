#include "datatest.h"
#include "ui_datatest.h"
#include <QDebug>
#define MAX(a, b) (a>b?a:b)

Single::Single(QString s)
{
    QStringList strList=s.split(",");
    for (int i=0;i<strList.size()&&i<3;i++)
        singleData.push_back(strList[i].toDouble());
    while(singleData.size()<3)
        singleData.push_back(0);
}

bool Single::equal(Single& other)
{
     if(!(singleData.size()==3&&other.singleData.size()==3))
         return false;
     for(int i=0;i<3;i++)
         if (singleData[i]!=other.singleData[i])
             return false;
     return true;
}

int Single::score(Single& other)
{
    if (equal(other))
        return 3;
    else
        return -1;
}

DataTest::DataTest(QVector<QString> data, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DataTest)
{
    ui->setupUi(this);
    for (auto&&d:data)
        this->data.push_back(Single(d));
    processData();
}

DataTest::~DataTest()
{
    delete ui;
}

void DataTest::processData()
{
    QVector<Single> a;
    for (int i=0;i<data.size()/4;i++)
        a.push_back(data[i]);
    QVector<Single> b;
    for (int i=data.size()/4;i<2*data.size()/4;i++)
        b.push_back(data[i]);
    QVector<Single> c;
    for (int i=2*data.size()/4;i<3*data.size()/4;i++)
        c.push_back(data[i]);
    QVector<Single> d;
    for (int i=3*data.size()/4;i<data.size();i++)
        d.push_back(data[i]);

    // remove more data
    while (d.size()!=a.size())
        d.pop_back();

    QVector<QVector<double>> a_heapmap = caculateHeapMap(a, CaculateType::DIRECT);

    for (auto&& h:a_heapmap)
    {
        for (auto&& a:h)
        {
            qDebug()<<a;
        }
    }

}

QVector<QVector<double>> DataTest::caculateHeapMap(QVector<Single>& originData, CaculateType type)
{
    QVector<Single> first;
    for (int i=0;i<originData.size()/2;i++)
        first.push_back(originData[i]);
    QVector<Single> second;
    if (type==CaculateType::SYMMETRY)
    {
        for (int i=0;i<first.size();i++)
            second.push_back(originData[originData.size()-i]);
    }else{
        for (int i=0;i<first.size();i++)
            second.push_back(originData[i+originData.size()/2]);
    }
    return caculateHeapMap(first,second);
}

QVector<QVector<double>> DataTest::caculateHeapMap(QVector<Single>& leftData, QVector<Single>& rightData)
{
    QVector<QVector<double>> matrix=QVector<QVector<double>>(leftData.size()+1,QVector<double>(rightData.size()+1,0));
    for (int i=1;i<leftData.size()+1;i++)
    {
        for (int j=1;j<rightData.size()+1;j++)
        {
            int maxScore=0;
            maxScore=MAX(matrix[i-1][j-1]+leftData[i-1].score(rightData[j-1]),maxScore);
            maxScore=MAX(matrix[i][j-1]-1,maxScore);
            maxScore=MAX(matrix[i-1][j]-1,maxScore);
            matrix[i][j]=maxScore;
        }
    }
    return matrix;
}
