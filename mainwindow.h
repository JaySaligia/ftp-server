#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dialog1.h"
#include "client.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
signals:
    void shownofile();//显示文件不存在错误
    void showpasvfailed();//显示被动模式开启错误
    void showuploadsuccess();//显示上传成功
    void showstopupload();//暂停上传
    void shownodir();//显示目录存在
    void shownodownloadfile();//显示未指定下载文件
    void showdownloadsuccess();//显示下载成功
    void showstopdownload();//暂停下载
private slots:

    void on_linkButton_clicked();

    void on_exitButton_clicked();

    void upload();

    void download();
    void finishlink();
    void stopdownload();
    void stopupload();
private:
    Ui::MainWindow *ui;
    Dialog1 dialog1;
    client newclinet;
};

#endif // MAINWINDOW_H
