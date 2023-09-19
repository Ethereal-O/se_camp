#ifndef WATERWINDOW_H
#define WATERWINDOW_H

#include <QMainWindow>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class WaterWindow;
}
QT_END_NAMESPACE

struct Weather
{
    int time;
    int location;
    int Weight;

    bool operator<(const Weather &y) const
    {
        return time < y.time; // 设定按照weather由小到大排列
    }
};

class WaterWindow : public QMainWindow
{
    Q_OBJECT

public:
    WaterWindow(QWidget *parent = nullptr);
    ~WaterWindow();
    void printLogo();
    void loadFile();
    void lastTime();
    void nextTime();
    void singleStep();
    void simFlow();
    std::vector<int> calcShortestPathSunny();
    std::vector<int> calcShortestPathWindy();

private:
    Ui::WaterWindow *ui;
    std::vector<int> *height;
    std::vector<int> *waters;
    std::vector<std::vector<int>> *graph;
    std::vector<Weather> *weathers;
    std::vector<int> sunnyPath;
    std::vector<int> windyPath;
    QVector<QLabel *> boxes;
    int time = 0;
    int calcShortestPathSunny_I(std::vector<int> &oldPath, int now);
    void setWidget();
    void updateWidget();
};
#endif // WATERWINDOW_H
