#include "udpworker.h"

UDPworker::UDPworker(QObject *parent) : QObject(parent)
{

}


/*!
 * @brief Метод инициализирует UDP сервер
 */
void UDPworker::InitSocket()
{

    serviceUdpSocket = new QUdpSocket(this);
    /*
     * Соединяем присваиваем адрес и порт серверу и соединяем функцию
     * обраотчик принятых пакетов с сокетом
     */
    serviceUdpSocket->bind(QHostAddress::LocalHost, BIND_PORT);
    connect(serviceUdpSocket, &QUdpSocket::readyRead, this, &UDPworker::readPendingDatagrams);

    serviceUdpSocket_String = new QUdpSocket(this);
    serviceUdpSocket_String->bind(QHostAddress::LocalHost, BIND_PORT_STRING);
    connect(serviceUdpSocket_String, &QUdpSocket::readyRead, this, &UDPworker::readPendingDatagrams_String);

}

/*!
 * @brief Метод осуществляет обработку принятой датаграммы
 */
void UDPworker::ReadDatagram(QNetworkDatagram datagram)
{
    QByteArray data;
    data = datagram.data();

    QDataStream inStr(&data, QIODevice::ReadOnly);
    QDateTime dateTime;

    inStr >> dateTime;

    emit sig_sendTimeToGUI(dateTime);
}

void UDPworker::ReadDatagram_String(QNetworkDatagram datagram)
{
    QByteArray data;
    data = datagram.data();

    //QDataStream inStr(&data, QIODevice::ReadOnly);
    //QString string;
    //inStr >> string;

    QString size = QString::number(data.size());
    QString address = serviceUdpSocket_String->localAddress().toString();

    emit sig_sendStringToGUI(size, address);
}

/*!
 * @brief Метод осуществляет опередачу датаграммы
 */
void UDPworker::SendDatagram(QByteArray data)
{
    /*
     *  Отправляем данные на localhost и задефайненный порт
     */
    serviceUdpSocket->writeDatagram(data, QHostAddress::LocalHost, BIND_PORT);
}

void UDPworker::SendDatagram_String(QByteArray data)
{
    serviceUdpSocket_String->writeDatagram(data, QHostAddress::LocalHost, BIND_PORT_STRING);
}

/*!
 * @brief Метод осуществляет чтение датаграм из сокета
 */
void UDPworker::readPendingDatagrams( void )
{
    /*
     *  Производим чтение принятых датаграмм
     */
    while(serviceUdpSocket->hasPendingDatagrams()){
            QNetworkDatagram datagram = serviceUdpSocket->receiveDatagram();
            ReadDatagram(datagram);
    }

}

void UDPworker::readPendingDatagrams_String( void )
{
    while(serviceUdpSocket_String->hasPendingDatagrams()){
            QNetworkDatagram datagram = serviceUdpSocket_String->receiveDatagram();
            ReadDatagram_String(datagram);
    }

}
