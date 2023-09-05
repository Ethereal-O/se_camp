#ifndef HASHWINDOW_H
#define HASHWINDOW_H

#include <QMainWindow>

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

private:
    Ui::HashWindow *ui;
};
#endif // HASHWINDOW_H
