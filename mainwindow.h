#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dialog1.h"
#include "client.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_linkButton_clicked();

    void on_exitButton_clicked();

    void upload();
private:
    Ui::MainWindow *ui;
    Dialog1 dialog1;
    client newclinet;
};

#endif // MAINWINDOW_H
