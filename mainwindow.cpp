#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pwline->setEchoMode(QLineEdit::PasswordEchoOnEdit);
    connect(&dialog1,&Dialog1::showmainwindow,this,&MainWindow::finishlink);//收到来自Dialog1的showmainwindow信号后，执行后面的MainWindow::finishlink
    connect(&dialog1.dialogupload,&Dialogupload::getfilename,this,&MainWindow::upload);//收到来自dialogupload的getfilename信号后，执行upload
    connect(this, &MainWindow::shownofile, &dialog1.dialogupload, &Dialogupload::shownofilemsg);//给dialogupload发送不存在该文件的信号
    connect(this, &MainWindow::showpasvfailed, &dialog1.dialogupload, &Dialogupload::showpasvfailedmsg);//发送开启被动模式失败的信号
    connect(this, &MainWindow::showuploadsuccess, &dialog1.dialogupload, &Dialogupload::showuploadsuccessmsg);//发送文件上传成功的信号
    connect(&dialog1.dialogupload,&Dialogupload::getstopuploadmsg, this, &MainWindow::stopupload);
    connect(this, &MainWindow::showstopupload, &dialog1.dialogupload, &Dialogupload::showstopuploadmsg);

    connect(&dialog1.dialogdownload,&Dialogdownload::getdownloadmsg, this, &MainWindow::download);
    connect(&dialog1.dialogdownload,&Dialogdownload::getstopdownloadmsg, this, &MainWindow::stopdownload);
    connect(this, &MainWindow::shownodir, &dialog1.dialogdownload, &Dialogdownload::shownodirmsg);
    connect(this, &MainWindow::shownodownloadfile, &dialog1.dialogdownload, &Dialogdownload::shownodownloadfilemsg);
    connect(this, &MainWindow::showpasvfailed, &dialog1.dialogdownload, &Dialogdownload::showpasvfailedmsg);
    connect(this, &MainWindow::showdownloadsuccess, &dialog1.dialogdownload, &Dialogdownload::showdownloadsuccessmsg);
    connect(this, &MainWindow::showstopdownload, &dialog1.dialogdownload, &Dialogdownload::showstopdownloadmsg);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_linkButton_clicked()
{
    newclinet.ipaddr = ui->ipline->text().toStdString();
    newclinet.name = ui->nameline->text().toStdString();
    newclinet.pw = ui->pwline->text().toStdString();
    //测试
    switch (newclinet.linkstart()) {
    case -1: QMessageBox::information(this,"连接信息","初始化失败");break;
    case -2: QMessageBox::information(this,"连接信息","套接字生成失败");break;
    case -3: QMessageBox::information(this, "连接信息", "用户名密码认证失败");break;
    case -4: QMessageBox::information(this,"连接信息","未知错误");break;
    case 0: QMessageBox::information(this,"连接信息","连接服务器失败");break;
    case 1:
        QMessageBox::information(this,"连接信息","连接服务器成功");
        this->hide();
        dialog1.show();
        break;
    }


}

void MainWindow::on_exitButton_clicked()
{
    this->close();
}

void MainWindow::upload()//上传文件
{
    const char* openfile = dialog1.dialogupload.openFile.toStdString().c_str();
    switch(newclinet.upload(openfile)){
    case -1:emit shownofile();break;
    case -2:emit showpasvfailed();break;
    case 1:emit showuploadsuccess();break;
    }
}

void MainWindow::download()//下载文件
{
    const char *storedir = dialog1.dialogdownload.storeDir.toStdString().c_str();
    const char *downloadfile = dialog1.dialogdownload.downloadFile.toStdString().c_str();

    switch(newclinet.download(storedir, downloadfile)){
    case -1:emit shownodir();break;
    case -2:emit shownodownloadfile();break;
    case -3:emit showpasvfailed();break;
    case 1:emit showdownloadsuccess();break;
    }
}

void MainWindow::stopdownload()
{
    newclinet.finish();
    emit showstopdownload();
}

void MainWindow::stopupload()
{
    newclinet.finish();
    emit showstopupload();
}

void MainWindow::finishlink()
{
    newclinet.finish();
    this->show();
}
