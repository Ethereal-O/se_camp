#include "hashwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HashWindow w;
    w.show();
    return a.exec();
}
