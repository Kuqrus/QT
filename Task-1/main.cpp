#include "mainwindow.h"

#include <QApplication>

#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QMessageBox msg;

    msg.setText("Hello Qt!");
    msg.setIcon(QMessageBox::Information);
    msg.setStyleSheet("color : blue");
    msg.exec();

    return a.exec();
}
