#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->gb_rButtons->setTitle("Some illegal functions");

    ui->rb_button1->setText("Hack Pentagon");
    ui->rb_button2->setText("Update to C:\\Windows\\System33");

    ui->pb_toggleButton->setText("EXECUTE!");
    ui->pb_toggleButton->setCheckable(1);

    ui->progressBar->setRange(0, 10);
    ui->progressBar->setValue(0);

    for(int i = 1; i <= 10; i++){
        ui->cb_elements->addItem("Donwload " + QString::number(i) + "000 BitCoins");
    }



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_toggleButton_clicked()
{
    if(ui->progressBar->value() >= 10){
        ui->progressBar->setValue(0);
    }
    else{
        ui->progressBar->setValue(ui->progressBar->value() + 1);
    }
}

