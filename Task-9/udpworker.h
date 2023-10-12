#ifndef UDPWORKER_H
#define UDPWORKER_H

#include <QUdpSocket>
#include <QNetworkDatagram>
#include <QDateTime>


#define BIND_PORT 12345
#define BIND_PORT_STRING 11111

class UDPworker : public QObject
{
    Q_OBJECT
public:
    explicit UDPworker(QObject *parent = nullptr);
    void InitSocket( void );
    void ReadDatagram( QNetworkDatagram datagram);
    void SendDatagram(QByteArray data );

    void ReadDatagram_String( QNetworkDatagram datagram);
    void SendDatagram_String(QByteArray data);


private slots:
    void readPendingDatagrams(void);

    void readPendingDatagrams_String(void);

private:
    QUdpSocket* serviceUdpSocket;

    QUdpSocket* serviceUdpSocket_String;

signals:
    void sig_sendTimeToGUI(QDateTime data);
    void sig_sendStringToGUI(QString size, QString address);

};

#endif // UDPWORKER_H
