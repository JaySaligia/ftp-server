#include "dialog1.h"
#include "ui_dialog1.h"

Dialog1::Dialog1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog1)
{
    ui->setupUi(this);
    connect(&dialogdownload,&Dialogdownload::showdialog1down,this,&Dialog1::show);
    connect(&dialogupload,&Dialogupload::showdialog1up,this,&Dialog1::show);
}

Dialog1::~Dialog1()
{
    delete ui;
}

void Dialog1::on_backButton_clicked()
{
    emit showmainwindow();
    this->hide();
}

void Dialog1::on_downloadButton_clicked()
{
    this->hide();
    dialogdownload.show();
}

void Dialog1::on_uploadButton_clicked()
{
    this->hide();
    dialogupload.show();
}
