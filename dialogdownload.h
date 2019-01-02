#ifndef DIALOGDOWNLOAD_H
#define DIALOGDOWNLOAD_H

#include <QDialog>

namespace Ui {
class Dialogdownload;
}

class Dialogdownload : public QDialog
{
    Q_OBJECT

public:
    explicit Dialogdownload(QWidget *parent = 0);
    ~Dialogdownload();

signals:
    void showdialog1down();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Dialogdownload *ui;
};

#endif // DIALOGDOWNLOAD_H
