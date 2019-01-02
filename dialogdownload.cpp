#include "dialogdownload.h"
#include "ui_dialogdownload.h"

Dialogdownload::Dialogdownload(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialogdownload)
{
    ui->setupUi(this);
}

Dialogdownload::~Dialogdownload()
{
    delete ui;
}

void Dialogdownload::on_pushButton_clicked()
{
    emit showdialog1down();
    this->hide();
}
