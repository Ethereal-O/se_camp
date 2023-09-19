#include "hashwindow.h"
#include "ui_hashwindow.h"
#include <QDebug>

HashWindow::HashWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::HashWindow)
{
    ui->setupUi(this);
    connect(ui->keyEdit, &QLineEdit::textChanged, this, &HashWindow::setKey);
    connect(ui->valueEdit, &QLineEdit::textChanged, this, &HashWindow::setValue);
    connect(ui->insertButton, &QPushButton::clicked, this, &HashWindow::insertItem);
    connect(ui->deleteButton, &QPushButton::clicked, this, &HashWindow::deleteItem);

    QHBoxLayout *leftLayout = new QHBoxLayout();
    leftLayout->setDirection(QBoxLayout::TopToBottom); // verticalLayout
    leftLayout->setAlignment(Qt::AlignCenter);
    QHBoxLayout *rightLayout = new QHBoxLayout();
    rightLayout->setDirection(QBoxLayout::TopToBottom); // verticalLayout
    rightLayout->setAlignment(Qt::AlignCenter);
    for (int32_t i = 0; i < HASHSIZE; i++)
    {
        leftVector.push_back(new QLabel());
        leftVector[i]->setFixedSize(50, 50);
        leftVector[i]->setFrameShape(QFrame::Box);
        leftVector[i]->setText("nil");
        leftVector[i]->setAlignment(Qt::AlignCenter);
        leftLayout->addWidget(leftVector[i]);
        rightVector.push_back(new QLabel());
        rightVector[i]->setFixedSize(50, 50);
        rightVector[i]->setFrameShape(QFrame::Box);
        rightVector[i]->setText("nil");
        rightVector[i]->setAlignment(Qt::AlignCenter);
        rightLayout->addWidget(rightVector[i]);
    }
    ui->hashTableWidget_1->setLayout(leftLayout);
    ui->hashTableWidget_2->setLayout(rightLayout);

    hash = new CuckooHash(std::make_unique<CaculateHashNormal>());
}

HashWindow::~HashWindow()
{
    delete ui;
}

void HashWindow::DrawLineWithArrow(QPainter &painter, QPen pen, QPoint start, QPoint end)
{
    painter.setRenderHint(QPainter::Antialiasing, true);

    qreal arrowSize = 20;
    painter.setPen(pen);
    painter.setBrush(pen.color());

    QLineF line(end, start);

    double angle = std::atan2(-line.dy(), line.dx());
    QPointF arrowP1 = line.p1() + QPointF(sin(angle + M_PI / 3) * arrowSize,
                                          cos(angle + M_PI / 3) * arrowSize);
    QPointF arrowP2 = line.p1() + QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize,
                                          cos(angle + M_PI - M_PI / 3) * arrowSize);

    QPolygonF arrowHead;
    arrowHead.clear();
    arrowHead << line.p1() << arrowP1 << arrowP2;
    painter.drawLine(line);
    painter.drawPolygon(arrowHead);
}

void HashWindow::paintEvent(QPaintEvent *newPaintEvent)
{
    (void)newPaintEvent;
    QPainter painter(this);
    QPen pen = QPen();
    for (int i = 0; i < static_cast<int>(kickPath.size() - 1); i++)
        if (kickPath[i].first == 0 && kickPath[i].second >= 0 && kickPath[i].second < HASHSIZE && kickPath[i + 1].second >= 0 && kickPath[i + 1].second < HASHSIZE)
            DrawLineWithArrow(painter, pen, QPoint(ui->hashTableWidget_1->x() + leftVector[0]->x() + leftVector[0]->width(), ui->hashTableWidget_1->y() + leftVector[kickPath[i].second]->y() + leftVector[0]->height() / 2), QPoint(ui->hashTableWidget_2->x() + rightVector[0]->x(), ui->hashTableWidget_2->y() + rightVector[kickPath[i + 1].second]->y() + rightVector[0]->height() / 2));
        else if (kickPath[i].first == 1 && kickPath[i].second >= 0 && kickPath[i].second < HASHSIZE && kickPath[i + 1].second >= 0 && kickPath[i + 1].second < HASHSIZE)
            DrawLineWithArrow(painter, pen, QPoint(ui->hashTableWidget_2->x() + rightVector[0]->x(), ui->hashTableWidget_2->y() + rightVector[kickPath[i].second]->y() + rightVector[0]->height() / 2), QPoint(ui->hashTableWidget_1->x() + leftVector[0]->x() + leftVector[0]->width(), ui->hashTableWidget_1->y() + leftVector[kickPath[i + 1].second]->y() + leftVector[0]->height() / 2));
}

void HashWindow::updateShow()
{
    auto originHashTable = hash->GetHashTable();
    for (int i = 0; i < HASHSIZE; i++)
        leftVector[i]->setText(originHashTable[0][i].has_value() ? QString::number(originHashTable[0][i].value().second) : "nil");
    if (originHashTable.size() > 1)
        for (int i = 0; i < HASHSIZE; i++)
            rightVector[i]->setText(originHashTable[1][i].has_value() ? QString::number(originHashTable[1][i].value().second) : "nil");
}

void HashWindow::setKey()
{
    key = ui->keyEdit->text().toInt();
}

void HashWindow::setValue()
{
    value = ui->valueEdit->text().toInt();
}

void HashWindow::insertItem()
{
    hash->Set(key, value);
    kickPath = hash->GetKickPath();
    updateShow();
    update();
}

void HashWindow::deleteItem()
{
    hash->Delete(key);
    kickPath.clear();
    updateShow();
    update();
}
