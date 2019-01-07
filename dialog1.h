#ifndef DIALOG1_H
#define DIALOG1_H

#include <QDialog>
#include "dialogdownload.h"
#include "dialogupload.h"


namespace Ui {
class Dialog1;
}

class Dialog1 : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog1(QWidget *parent = 0);
    ~Dialog1();
    Dialogdownload dialogdownload;
    Dialogupload dialogupload;

signals:
    void showmainwindow();

private slots:
    void on_backButton_clicked();

    void on_downloadButton_clicked();

    void on_uploadButton_clicked();

private:
    Ui::Dialog1 *ui;

};

#endif // DIALOG1_H
