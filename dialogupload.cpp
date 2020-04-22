#include "dialogupload.h"
#include "ui_dialogupload.h"
#include <QFileDialog>
#include <QMessageBox>

Dialogupload::Dialogupload(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialogupload)
{
    ui->setupUi(this);
    ui->csfileLine->setFocusPolicy(Qt::NoFocus);
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
    ui->csfileLine->setText(openFile);
}

void Dialogupload::shownofilemsg()
{
    QMessageBox::information(this,"错误信息","未选中任何文件或文件不存在");
}

void Dialogupload::showpasvfailedmsg()
{
    QMessageBox::information(this,"错误信息","被动连接开启失败");
}

void Dialogupload::showuploadsuccessmsg()
{
    QMessageBox::information(this,"信息","文件上传成功");
}

void Dialogupload::on_uploadstartButton_clicked()
{
    QMessageBox::information(this,"信息","开始上传");
    emit getfilename();
}

void Dialogupload::on_uploadstopButton_clicked()
{
    emit getstopuploadmsg();
}

void Dialogupload::showstopuploadmsg()
{
    QMessageBox::information(this,"信息","上传已暂停");
}
