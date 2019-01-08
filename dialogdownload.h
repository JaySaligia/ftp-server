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
    QString storeDir = "";
    QString downloadFile = "";

    void shownodirmsg();
    void shownodownloadfilemsg();
    void showpasvfailedmsg();
    void showdownloadsuccessmsg();

signals:
    void showdialog1down();
    void getdownloadmsg();
private slots:
    void on_pushButton_clicked();

    void on_stfileButton_clicked();

    void on_downloadstartButton_clicked();

private:
    Ui::Dialogdownload *ui;
};

#endif // DIALOGDOWNLOAD_H
