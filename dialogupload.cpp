#include "dialogupload.h"
#include "ui_dialogupload.h"

Dialogupload::Dialogupload(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialogupload)
{
    ui->setupUi(this);
}

Dialogupload::~Dialogupload()
{
    delete ui;
}

void Dialogupload::on_backButton_clicked()
{
    emit showdialog1up();
    this->hide();
}
