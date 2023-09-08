#include "waterwindow.h"
#include "ui_waterwindow.h"
#include <bits/stdc++.h>
#include <QFileDialog>
#include <QDebug>

WaterWindow::WaterWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::WaterWindow)
{
    ui->setupUi(this);
    connect(ui->loadFileBtn, &QPushButton::clicked, this, &WaterWindow::loadFile);
    connect(ui->lastTimeBtn, &QPushButton::clicked, this, &WaterWindow::lastTime);
    connect(ui->nextTimeBtn, &QPushButton::clicked, this, &WaterWindow::nextTime);

    printLogo();
}

WaterWindow::~WaterWindow()
{
    delete ui;
}

void WaterWindow::setWidget()
{
    for (int i = 0; i < static_cast<int>(waters->size()); i++)
        boxes.push_back(new QLabel());

    QGridLayout *layout = new QGridLayout();
    layout->setAlignment(Qt::AlignCenter);
    for (int i = 0; i < static_cast<int>(waters->size()); i++)
    {
        layout->addWidget(boxes[i], i / 5, i % 5);
        boxes[i]->setAlignment(Qt::AlignCenter);
        boxes[i]->setFrameShape(QFrame::Box);
        boxes[i]->setText("地点：" + QString::number(i) + "\n高度：" + QString::number(height->at(i)) + "\n积水量：" + QString::number(waters->at(i)));
    }
    if (boxes.size() > 0)
        boxes[0]->setStyleSheet("background-color:red;");

    for (int i = 0; i < static_cast<int>(waters->size() / 5); i++)
        layout->setRowStretch(i, 1);

    for (int i = 0; i < 5; i++)
        layout->setColumnStretch(i, 1);

    ui->waterShower->setLayout(layout);
    ui->timeShower->setText("当前时刻：" + QString::number(time));
}

void WaterWindow::updateWidget()
{
    for (int i = 0; i < static_cast<int>(waters->size()); i++)
    {
        boxes[i]->setText("地点：" + QString::number(i) + "\n高度：" + QString::number(height->at(i)) + "\n积水量：" + QString::number(waters->at(i)));
        int index = windyPath[std::min(static_cast<int>(windyPath.size()) - 1, time)];
        if (i == index)
            boxes[i]->setStyleSheet("background-color:red;");
        else if (waters->at(i) > 0)
            boxes[i]->setStyleSheet("background-color:blue;");
        else
            boxes[i]->setStyleSheet("background-color:white;");
    }
    ui->timeShower->setText("当前时刻：" + QString::number(time));
}

void WaterWindow::printLogo()
{
    qDebug() << ("\n\
       SSSSS    JJJJJJJJJ    TTTTTTTTT       UUU      UU\n\
     SSSS SSS      JJJ         TTT           UU      UUU\n\
     SS     SS      JJ          TT           UU      UU\n\
     SSS            JJ          TT          UU       UU\n\
      SSSSS         JJ          TT          UU      UU\n\
       SSS          JJ         TTT          UU      UU\n\
         SS        JJJ         TT           UU     UU\n\
    SSS SSS     JJ JJ          TT            UU   UU\n\
     SSSSS      JJJJJ         TTT            UUUUUU\n");
}

void WaterWindow::loadFile()
{
    QFileDialog f(this);
    f.setWindowTitle("选择文件");
    f.setViewMode(QFileDialog::Detail);

    if (f.exec() != QDialog::Accepted)
        return;

    QFile file(f.selectedFiles()[0]);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream readStream(&file);

    int N, M, R;
    std::stringstream ss(readStream.readLine().toStdString());
    ss >> N >> M;
    height = new std::vector<int>(N);
    waters = new std::vector<int>(N, 0);
    graph = new std::vector<std::vector<int>>(N);
    ss = std::stringstream(readStream.readLine().toStdString());

    for (int i = 0; i < N; i++)
    {
        int h;
        ss >> h;
        height->at(i) = h;
    }
    setWidget();

    for (int i = 0; i < M; i++)
    {
        ss = std::stringstream(readStream.readLine().toStdString());
        int from, to;
        ss >> from >> to;
        graph->at(from).push_back(to);
        graph->at(to).push_back(from);
    }

    for (int i = 0; i < N; i++)
    {
        std::sort(graph->at(i).begin(), graph->at(i).end(), [&](int l, int r)
                  { return height->at(l) > height->at(r); });
    }

    int maxIdx = -1, maxD = -1;
    for (int i = 0; i < N; i++)
    {
        if (static_cast<int>(graph->at(i).size()) > maxD)
        {
            maxIdx = i;
            maxD = graph->at(i).size();
        }
    }

    qDebug() << maxIdx;

    ss = std::stringstream(readStream.readLine().toStdString());
    ss >> R;

    weathers = new std::vector<Weather>();

    for (int i = 0; i < R; i++)
    {
        int t, l, w;
        ss = std::stringstream(readStream.readLine().toStdString());
        ss >> t >> l >> w;
        weathers->push_back({t, l, w});
    }

    std::sort(weathers->begin(), weathers->end(), std::less<Weather>());

    simFlow();

    sunnyPath = calcShortestPathSunny();
    windyPath = calcShortestPathWindy();

    qDebug() << sunnyPath.size() - 1 << " " << windyPath.size() - 1;

    QString out;
    for (auto &&p : windyPath)
    {
        out += QString::number(p) + ",";
    }

    out = out.mid(0, out.size() - 1);

    qDebug() << out;
}

void WaterWindow::singleStep()
{
    std::vector<int> changeWater(height->size());

    // step1: 每个先减去1
    for (auto &&w : *waters)
    {
        if (w > 0)
            w--;
    }

    // step2: 向周边流动
    for (int i = 0; i < static_cast<int>(waters->size()); i++)
    {
        if (waters->at(i) > 0)
        {
            int tot = waters->at(i);
            for (int j = 0; j < static_cast<int>(graph->at(i).size()); j++)
            {
                if (height->at(graph->at(i).at(j)) >= height->at(i))
                {
                    continue;
                }
                if (tot > 0)
                {
                    changeWater[graph->at(i).at(j)]++;
                    changeWater[i]--;
                    tot--;
                    //                    qDebug()<<i<<"->"<<graph->at(i).at(j);
                }
            }
        }
    }

    // step3: 下雨
    for (int i = 0; i < static_cast<int>(weathers->size()); i++)
    {
        if (weathers->at(i).time == time + 1)
        {
            changeWater[weathers->at(i).location] += weathers->at(i).Weight;
        }
        if (weathers->at(i).time > time + 1)
        {
            break;
        }
    }

    // step4: 赋值
    for (int i = 0; i < static_cast<int>(waters->size()); i++)
    {
        waters->at(i) += changeWater[i];
    }
    time++;

    //    qDebug()<<"new step"<<time;
    //    for(int i=0;i<static_cast<int>(waters->size());i++)
    //    {
    //        qDebug()<<waters->at(i);
    //    }
}

void WaterWindow::simFlow()
{
    while (true)
    {
        singleStep();
        if (time < weathers->at(weathers->size() - 1).time)
            continue;

        bool flag = false;
        for (auto &&l : *waters)
        {
            if (l > 0)
            {
                flag = true;
                break;
            }
        }
        if (!flag)
            break;
    }
    qDebug() << time;
    waters = new std::vector<int>(waters->size());
    time = 0;
}

std::vector<int> WaterWindow::calcShortestPathSunny()
{
    std::vector<std::vector<int>> oldLength(waters->size());

    oldLength.at(0).push_back(0);

    while (oldLength.at(oldLength.size() - 1).size() == 0)
    {
        std::vector<std::vector<int>> newLength(waters->size());
        for (int i = 0; i < static_cast<int>(newLength.size()); i++)
        {
            if (oldLength[i].size() == 0)
                continue;
            for (int j = 0; j < static_cast<int>(graph->at(i).size()); j++)
            {
                if (newLength[graph->at(i).at(j)].size() == 0)
                {
                    auto v = oldLength[i];
                    v.push_back(graph->at(i).at(j));
                    newLength[graph->at(i).at(j)] = v;
                }
            }

            if (newLength[i].size() == 0)
            {
                newLength[i] = oldLength[i];
            }
        }

        oldLength = newLength;
    }

    return oldLength.at(oldLength.size() - 1);
}

int WaterWindow::calcShortestPathSunny_I(std::vector<int> &oldPath, int now)
{
    if (now == static_cast<int>(graph->size() - 1))
    {
        oldPath.push_back(graph->size() - 1);
        return oldPath.size();
    }

    int LENGTH = INT_MAX;
    for (int i = 0; i < static_cast<int>(graph->at(now).size()); i++)
    {
        bool flag = false;
        for (auto &&old : oldPath)
        {
            if (old == graph->at(now).at(i))
            {
                flag = true;
                break;
            }
        }
        if (flag)
        {
            continue;
        }

        std::vector<int> newPath = oldPath;
        newPath.push_back(now);
        int res = calcShortestPathSunny_I(newPath, graph->at(now).at(i));
        if (res < LENGTH)
        {
            oldPath = newPath;
            LENGTH = res;
        }
    }
    return LENGTH;
}

std::vector<int> WaterWindow::calcShortestPathWindy()
{
    std::vector<std::vector<int>> oldLength(waters->size());

    oldLength.at(0).push_back(0);

    while (oldLength.at(oldLength.size() - 1).size() == 0)
    {
        std::vector<std::vector<int>> newLength(waters->size());
        singleStep();
        auto newWaters = *waters;
        for (int i = 0; i < static_cast<int>(newLength.size()); i++)
        {
            if (oldLength[i].size() == 0)
                continue;
            for (int j = 0; j < static_cast<int>(graph->at(i).size()); j++)
            {
                if (newWaters[graph->at(i).at(j)] == 0 && newLength[graph->at(i).at(j)].size() == 0)
                {
                    auto v = oldLength[i];
                    v.push_back(graph->at(i).at(j));
                    newLength[graph->at(i).at(j)] = v;
                }
            }
            if (newWaters[i] == 0)
            {
                if (newLength[i].size() == 0 || oldLength[i].size() + 1 < newLength[i].size())
                {
                    newLength[i] = oldLength[i];
                    newLength[i].push_back(i);
                }
            }
            else
            {
                newLength[i].clear();
            }
        }

        oldLength = newLength;
    }

    time = 0;
    waters = new std::vector<int>(waters->size());

    return oldLength.at(oldLength.size() - 1);
}

void WaterWindow::lastTime()
{
    int newTime = time > 0 ? time - 1 : time;
    time = 0;

    for (auto &&water : *waters)
        water = 0;

    for (int i = 0; i < newTime; i++)
        singleStep();

    updateWidget();
}

void WaterWindow::nextTime()
{
    singleStep();
    updateWidget();
}
