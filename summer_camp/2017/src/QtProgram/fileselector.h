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

private:
    Ui::FileSelector *ui;
    QString filePath;
    void selectFile();
    void confirm();
};

#endif // FILESELECTOR_H
