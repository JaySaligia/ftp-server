#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(&dialog1,&Dialog1::showmainwindow,this,&MainWindow::show);//收到来自Dialog1的showmainwindow信号后，执行后面的MainWindow::show
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_linkButton_clicked()
{
    this->hide();
    dialog1.show();
}

void MainWindow::on_exitButton_clicked()
{
    this->close();
}
