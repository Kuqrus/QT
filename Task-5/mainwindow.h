#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "stopwatch.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void rcv_pb_lap_pressed();

private slots:
    void updateTime();

    void on_pb_start_toggled(bool checked);

    void on_pb_lap_clicked();

    void on_pb_clear_clicked();

private:

    Ui::MainWindow *ui;
    Stopwatch *stopwatch;
};
#endif // MAINWINDOW_H
