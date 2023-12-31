#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    int x = 0;

    udpWorker = new UDPworker(this);
    udpWorker->InitSocket();

    connect(udpWorker, &UDPworker::sig_sendTimeToGUI, this, &MainWindow::DisplayTime);
    connect(udpWorker, &UDPworker::sig_sendStringToGUI, this, &MainWindow::DisplayString);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [&]{

        QDateTime dateTime = QDateTime::currentDateTime();

        QByteArray dataToSend;
        QDataStream outStr(&dataToSend, QIODevice::WriteOnly);

        outStr << dateTime;

        udpWorker->SendDatagram(dataToSend);
        timer->start(TIMER_DELAY);
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::DisplayString(QString size, QString address)
{
    ui->te_result->append("Принято сообщение от: " + address + ", размер сообщения " + size + " байт.");
}

void MainWindow::SendString(QString data)
{
    QByteArray DataToSend;
    QDataStream Str(&DataToSend, QIODevice::WriteOnly);
    Str << data;

    udpWorker->SendDatagram_String(DataToSend);
}

void MainWindow::on_pb_sendData_clicked()
{
    SendString(ui->te_enterData->toPlainText());
}

void MainWindow::on_pb_start_clicked()
{
    timer->start(TIMER_DELAY);
}

void MainWindow::DisplayTime(QDateTime data)
{
    counterPck++;
    if(counterPck % 20 == 0){
        ui->te_result->clear();
    }

    ui->te_result->append("Текущее время: " + data.toString() + ". "
                "Принято пакетов " + QString::number(counterPck));
}

void MainWindow::on_pb_stop_clicked()
{
    timer->stop();
}




