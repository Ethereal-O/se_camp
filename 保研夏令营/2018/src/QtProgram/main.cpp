#include "fileselector.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FileSelector w;
    w.show();
    return a.exec();
}
