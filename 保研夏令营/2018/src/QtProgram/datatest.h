#ifndef DATATEST_H
#define DATATEST_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class DataTest; }
QT_END_NAMESPACE

class Single{
public:
    Single(){}
    Single(QString s);
    bool equal(Single& other);
    int score(Single& other);
    QVector<double> singleData;
};

class DataTest : public QMainWindow
{
    Q_OBJECT

public:
    DataTest(QVector<QString> data, QWidget *parent = nullptr);
    ~DataTest();

private:
    enum CaculateType{
        DIRECT,
        SYMMETRY
    };
    Ui::DataTest *ui;
    QVector<Single> data;
    void processData();
    QVector<QVector<double>> caculateHeapMap(QVector<Single>& originData, CaculateType type);
    QVector<QVector<double>> caculateHeapMap(QVector<Single>& leftData, QVector<Single>& rightData);
};
#endif // DATATEST_H
