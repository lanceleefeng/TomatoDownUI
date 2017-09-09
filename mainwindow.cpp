#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //ui->setTitle("go");
    //ui->setWindowTitle("go");

    // setTitle("fuck");
    //setWindowTitle("fuck");

    ui->setupUi(this);

    //setWindowTitle("fuck");
    setWindowTitle("番茄倒计时");



}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_hide_clicked()
{

    bool visible = ui->pushButton_restart->isVisible();
    
    if(visible){
        ui->pushButton_restart->hide();
    }else{
        ui->pushButton_restart->show();
    }
}
