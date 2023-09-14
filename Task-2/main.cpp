//#include "mainwindow.h"

#include <QApplication>
#include <QtNetwork>
#include <QtSQL>

#include <QMessageBox>

void TestingQtNework(){
    QMessageBox msg;
    QNetworkAddressEntry address;
    QNetworkInterface interface;

    QString ip;

    foreach(interface, QNetworkInterface::allInterfaces()){
        if(interface.flags().testFlag(QNetworkInterface::IsUp) && !interface.flags().testFlag(QNetworkInterface::IsLoopBack)){
            foreach(address, interface.addressEntries()){
                if(address.ip().toString().contains(".")){
                    ip = address.ip().toString();
                }
            }
        }
    }

    msg.setWindowTitle("QtNet Test");
    msg.setText(ip);

    msg.exec();
}

void TestingQtSql(){
    QMessageBox msg;
    QString str;
    QSqlDatabase sql;

    if(!sql.isOpen()){
        str = "DB is NOT open!";
    }

    msg.setWindowTitle("QtSql Test");
    msg.setText(str);
    msg.exec();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;

    TestingQtNework();
    TestingQtSql();

    return a.exec();
}
