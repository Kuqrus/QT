#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    NI = new NameInput(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_editName_clicked()
{
    NI->show();
}

void MainWindow::on_pb_connect_clicked()
{
    close();
}

