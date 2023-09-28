#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    stopwatch = new Stopwatch(this);

    ui->pb_lap->setEnabled(0);
    ui->label_seconds->setText(stopwatch->GetTime());

    connect(stopwatch, &Stopwatch::sig_pb_lap_pressed, this, &MainWindow::rcv_pb_lap_pressed);
    connect(stopwatch, &Stopwatch::sig_start_toggled, this, &MainWindow::updateTime);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::rcv_pb_lap_pressed()
{
    ui->tb_times->append(stopwatch->GetLapTime());
}

void MainWindow::updateTime()
{
    ui->label_seconds->setText(stopwatch->GetTime());
}


void MainWindow::on_pb_start_toggled(bool checked)
{
    stopwatch->Execute(checked);

    if(checked){
        ui->pb_lap->setEnabled(1);
        ui->pb_start->setText("Стоп");
    }
    else {
        ui->pb_lap->setEnabled(0);
        ui->pb_start->setText("Старт");
    }
}


void MainWindow::on_pb_lap_clicked()
{
    stopwatch->pb_lap_pressed();
}


void MainWindow::on_pb_clear_clicked()
{
    stopwatch->Clear();
    ui->label_seconds->setText(stopwatch->GetTime());
    ui->tb_times->clear();
}

