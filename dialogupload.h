#ifndef DIALOGUPLOAD_H
#define DIALOGUPLOAD_H

#include <QDialog>

namespace Ui {
class Dialogupload;
}

class Dialogupload : public QDialog
{
    Q_OBJECT

public:
    explicit Dialogupload(QWidget *parent = 0);
    ~Dialogupload();

signals:
    void showdialog1up();

private slots:
    void on_backButton_clicked();

private:
    Ui::Dialogupload *ui;
};

#endif // DIALOGUPLOAD_H
