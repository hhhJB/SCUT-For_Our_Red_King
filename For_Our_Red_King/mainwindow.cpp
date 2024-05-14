#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->setWindowTitle(QString("为了红王"));
    ui->setupUi(this);//设置主菜单ui界面
}

MainWindow::~MainWindow()
{
    delete ui;
}
