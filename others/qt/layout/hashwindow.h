#ifndef HASHWINDOW_H
#define HASHWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QLayout>
#include <QPainter>
#include "hash.h"

using Hash = Hash_T<int32_t, int32_t>;
using LinearHash = LinearHash_T<int32_t, int32_t>;
using CuckooHash = CuckooHash_T<int32_t, int32_t>;
using CaculateHashNormal = CaculateHashNormal_T<int32_t>;
using KeyType = int32_t;
using ValueType = int32_t;

const int32_t HASHSIZE = 8;

QT_BEGIN_NAMESPACE
namespace Ui
{
    class HashWindow;
}
QT_END_NAMESPACE

class HashWindow : public QMainWindow
{
    Q_OBJECT

public:
    HashWindow(QWidget *parent = nullptr);
    ~HashWindow();
    void setKey();
    void setValue();
    void insertItem();
    void deleteItem();
    void updateShow();
    void DrawLineWithArrow(QPainter &painter, QPen pen, QPoint start, QPoint end);
    void paintEvent(QPaintEvent *newPaintEvent);

private:
    Ui::HashWindow *ui;
    QVector<QLabel *> leftVector;
    QVector<QLabel *> rightVector;
    CuckooHash *hash;
    std::vector<std::pair<int32_t, int32_t>> kickPath;
    KeyType key;
    ValueType value;
};
#endif // HASHWINDOW_H
