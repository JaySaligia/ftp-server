#include "dialogupload.h"
#include "ui_dialogupload.h"
#include <QFileDialog>

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

void Dialogupload::on_csfileButton_clicked()
{
    openFile = QFileDialog::getOpenFileName(this, "打开", "c:\\", "*");
    emit getfilename();
}
