#include "dialogdownload.h"
#include "ui_dialogdownload.h"
#include <QFileDialog>
#include <QMessageBox>

Dialogdownload::Dialogdownload(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialogdownload)
{
    ui->setupUi(this);
    ui->stfileLine->setFocusPolicy(Qt::NoFocus);
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



void Dialogdownload::on_stfileButton_clicked()
{
     storeDir = QFileDialog::getExistingDirectory(this, "保存路径", "C:\\", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
     ui->stfileLine->setText(storeDir);
}

void Dialogdownload::on_downloadstartButton_clicked()
{
    downloadFile = ui->downloadfileLine->text();
    emit getdownloadmsg();
}

void Dialogdownload::on_downloadstopButton_clicked()
{
    emit getstopdownloadmsg();
}

void Dialogdownload::shownodirmsg()
{
    QMessageBox::information(this,"错误信息","未指定文件保存目录或目录不存在");
}

void Dialogdownload::shownodownloadfilemsg()
{
    QMessageBox::information(this,"错误信息","未指定下载文件或下载文件不存在");
}

void Dialogdownload::showpasvfailedmsg()
{
    QMessageBox::information(this,"错误信息","被动连接开启失败");
}

void Dialogdownload::showdownloadsuccessmsg()
{
    QMessageBox::information(this,"信息","下载成功");
}

void Dialogdownload::showstopdownloadmsg()
{
    QMessageBox::information(this,"信息","下载已暂停");
}
