#ifndef FILESELECTOR_H
#define FILESELECTOR_H

#include <QMainWindow>

namespace Ui {
class FileSelector;
}

class FileSelector : public QMainWindow
{
    Q_OBJECT

public:
    explicit FileSelector(QWidget *parent = nullptr);
    ~FileSelector();
    void selectFile();
    void inputFile();
    void confirm();

private:
    Ui::FileSelector *ui;
    QString filePath;
};

#endif // FILESELECTOR_H
