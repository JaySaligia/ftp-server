#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_linkbutton_clicked()
{
    QMessageBox::information(this,"图形界面",ui->ipline->text());
    this->hide();
    dialog1.show();
    dialog1.exec();
    this->show();
}

void MainWindow::on_pushButton_clicked()
{
    this->close();
}
