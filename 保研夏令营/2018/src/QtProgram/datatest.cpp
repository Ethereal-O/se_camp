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

void DataTest::checkReal(int score)
{
    if (score>5)
        ui->checkRes->setText("假");
}

void DataTest::paintHeapMap(QCustomPlot* plot, QVector<QVector<double>>& data, Range x_r, Range y_r)
{
        if (data.size()<=0)
            return;
        plot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom);//可拖拽+可滚轮缩放
       // fp3->axisRect()->insetLayout() ->setInsetAlignment(0,Qt::AlignRight|Qt::AlignTop); //图例置于右上
        /*
        Qt::AlignLeft|Qt::AlignTop); //图例置于左上
        Qt::AlignCenter|Qt::AlignTop);//图例置于中上
        Qt::AlignRight|Qt::AlignTop);//图例置于右上
        Qt::AlignLeft|Qt::AlignCenter);//图例置于左中
        Qt::AlignCenter);             //图例置于正中
        Qt::AlignRight|Qt::AlignCenter);//图例置于右中
        Qt::AlignLeft|Qt::AlignBottom);//图例置于左下
        Qt::AlignCenter|Qt::AlignBottom);//图例置于中下*/


       // fp3->legend->setVisible(true);//显示图例
//        plot->xAxis->setLabel("x_index");//x轴显示文字
//        plot->yAxis->setLabel("y_index");//y轴显示文字
        plot->xAxis->setRange(x_r.from,x_r.to);//当前X轴显示范围
        plot->yAxis->setRange(y_r.from,y_r.to);//当前y轴显示范围

     /*   //每条曲线都会独占一个graph()
        fp3->addGraph();
        fp3->graph(0)->setPen(QPen(Qt::blue));//曲线颜色

        fp3->graph(0)->setBrush(QBrush(QColor(0,255,255,20)));//曲线与X轴包围区的颜色
        //自动调整XY轴的范围，以便显示出graph(0)中所有的点
        //给第一个graph设置rescaleAxes()，后续所有graph都设置rescaleAxes(true)即可实现显示所有曲线
        fp3->graph(0)->rescaleAxes();*/

        //通过传递的轴的QCustomPlot进行注册,简洁理解QCPColorMap的数据为（x轴，y轴;颜色，值value）
        QCPColorMap *m_pColorMap = new QCPColorMap(plot->xAxis,plot->yAxis);
        m_pColorMap->data()->setSize(data.size(),data[0].size());//设置整个图（x,y）点数
        m_pColorMap->data()->setRange(QCPRange(x_r.from,x_r.to),QCPRange(y_r.from,y_r.to));//setRange是设置X轴以及Y轴的范围

        //颜色范围 == 色条
       /* m_pColorScale = new QCPColorScale(fp3);
        fp3->plotLayout()->addElement(0,1,m_pColorScale);//默认右侧添加色彩图
        m_pColorScale->setType(QCPAxis::atRight);
        m_pColorScale->setDataRange(QCPRange(0, 100));//颜色范围对应的取值范围data_maxColorBar这里为测量得到的最大值来代表颜色的最大值
        m_pColorScale->axis()->ticker()->setTickCount(6);
        m_pColorScale->axis()->setLabel("色彩");//色条的名

       // m_pColorMap->setColorScale(m_pColorScale); //热图连接色条

        m_pColorMap->setGradient(QCPColorGradient::gpCold);//设置默认渐进色变化（可在QCPColorGradient中查看）
     // QSharedPointer<QCPColorGradient> colorLayout(new QCPColorGradient);//生成颜色渐进变化对象
        QMap<double, QColor> color_layout;
        m_pColorGradient = new QCPColorGradient();//自定义的渐进色变化对象
        //m_pColorGradient->setColorStops(colorLayout);//QMap<double, QColor> color_layout为;颜*色*布局范围(double取值为0，1)
        m_pColorMap->setGradient(*m_pColorGradient);//设置渐进色变化
        m_pColorMap->rescaleDataRange();

        QCPMarginGroup *marginGroup = new QCPMarginGroup(fp3);
        fp3->axisRect()->setMarginGroup(QCP::msBottom | QCP::msTop, marginGroup);
        m_pColorScale->setMarginGroup(QCP::msBottom | QCP::msTop, marginGroup);*/

      for(int x=0;x<data.size();x++)
      {
        for(int y=0;y<data[x].size();y++)
        {
            m_pColorMap->data()->setCell(x,y,data[x][y]);
        }
      }
        m_pColorMap->setGradient(QCPColorGradient::gpHot);//设置默认渐进色变化（可在QCPColorGradient中查看）
        m_pColorMap->rescaleDataRange(true);

    // 立即刷新图像
        plot->rescaleAxes();//自适应大小
        plot->replot();
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
    paintHeapMap(ui->direct_1, a_heapmap, Range(0, data.size()/8), Range(data.size()/8, 2*(data.size()/8)));

    QVector<QVector<double>> b_heapmap = caculateHeapMap(b, CaculateType::DIRECT);
    paintHeapMap(ui->direct_2, b_heapmap, Range(2*(data.size()/8), 3*(data.size()/8)), Range(3*(data.size()/8), 4*(data.size()/8)));

    QVector<QVector<double>> c_heapmap = caculateHeapMap(c, CaculateType::DIRECT);
    paintHeapMap(ui->direct_3, c_heapmap, Range(4*(data.size()/8), 5*(data.size()/8)), Range(5*(data.size()/8), 6*(data.size()/8)));

    QVector<QVector<double>> d_heapmap = caculateHeapMap(d, CaculateType::DIRECT);
    paintHeapMap(ui->direct_4, d_heapmap, Range(6*(data.size()/8), 7*(data.size()/8)), Range(7*(data.size()/8), 8*(data.size()/8)));


    QVector<QVector<double>> e_heapmap = caculateHeapMap(a, CaculateType::SYMMETRY);
    paintHeapMap(ui->symmetry_1, e_heapmap, Range(0, data.size()/8), Range(2*(data.size()/8), (data.size()/8)));

    QVector<QVector<double>> f_heapmap = caculateHeapMap(b, CaculateType::SYMMETRY);
    paintHeapMap(ui->symmetry_2, f_heapmap, Range(2*(data.size()/8), 3*(data.size()/8)), Range(4*(data.size()/8), 3*(data.size()/8)));

    QVector<QVector<double>> g_heapmap = caculateHeapMap(c, CaculateType::SYMMETRY);
    paintHeapMap(ui->symmetry_3, g_heapmap, Range(4*(data.size()/8), 5*(data.size()/8)), Range(6*(data.size()/8), 5*(data.size()/8)));

    QVector<QVector<double>> h_heapmap = caculateHeapMap(d, CaculateType::SYMMETRY);
    paintHeapMap(ui->symmetry_4, h_heapmap, Range(6*(data.size()/8), 7*(data.size()/8)), Range(8*(data.size()/8), 7*(data.size()/8)));



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
            second.push_back(originData[originData.size()-i-1]);
    }else{
        for (int i=0;i<first.size();i++)
            second.push_back(originData[i+originData.size()/2]);
    }
    return caculateHeapMap(first,second);
}

QVector<QVector<double>> DataTest::caculateHeapMap(QVector<Single>& leftData, QVector<Single>& rightData)
{
    QVector<QVector<double>> matrix=QVector<QVector<double>>(leftData.size()+1,QVector<double>(rightData.size()+1,0));

    int maxmaxScore=0;
    for (int i=1;i<leftData.size()+1;i++)
    {
        for (int j=1;j<rightData.size()+1;j++)
        {
            int maxScore=0;
            maxScore=MAX(matrix[i-1][j-1]+leftData[i-1].score(rightData[j-1]),maxScore);
            maxScore=MAX(matrix[i][j-1]-1,maxScore);
            maxScore=MAX(matrix[i-1][j]-1,maxScore);
            matrix[i][j]=maxScore;
            maxmaxScore=MAX(maxScore,maxmaxScore);
        }
    }

    checkReal(maxmaxScore);
    return matrix;
}
