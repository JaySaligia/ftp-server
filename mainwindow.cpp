#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pwline->setEchoMode(QLineEdit::PasswordEchoOnEdit);
    connect(&dialog1,&Dialog1::showmainwindow,this,&MainWindow::show);//收到来自Dialog1的showmainwindow信号后，执行后面的MainWindow::show
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_linkButton_clicked()
{
    client newclinet;
    newclinet.ipaddr = ui->ipline->text().toStdString();
    newclinet.name = ui->nameline->text().toStdString();
    newclinet.pw = ui->pwline->text().toStdString();
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
