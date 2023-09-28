#include "stopwatch.h"

Stopwatch::Stopwatch(QObject *parent)
    : QObject{parent}
{    
    timer = new QTimer(this);

    connect(timer, &QTimer::timeout, this, &Stopwatch::Counting);
}

void Stopwatch::pb_lap_pressed()
{
    emit sig_pb_lap_pressed();
}

QString Stopwatch::TimeToString(double ms_sec, int min)
{
    QString str_min = QString::number(min);
    str_min = str_0.fill('0', 2 - str_min.size()) + str_min;

    QString str_ms_sec = QString::number(ms_sec, 'f', 1);
    str_ms_sec = str_0.fill('0', 4 - str_ms_sec.size()) + str_ms_sec;

    return str_min + ":" + str_ms_sec;
}

void Stopwatch::Clear()
{
    ms_sec = 0, min = 0;
    lap_ms_sec = 0, lap_min = 0;
    lap = 0;
    time = "00:00.0";
    lap_time = "00:00.0";
}

void Stopwatch::Counting()
{
    if(ms_sec <= 59.9) {
        ms_sec += 0.1;
    }
    else {
        min++;
        ms_sec = 0.0;
    }

    if(lap_ms_sec <= 59.9) {
        lap_ms_sec += 0.1;
    }
    else {
        lap_min++;
        lap_ms_sec = 0.0;
    }
    time = TimeToString(ms_sec, min);

    emit sig_start_toggled();
}

QString Stopwatch::GetTime()
{
    return time;
}

QString Stopwatch::GetLapTime()
{
    lap++;
    lap_time = TimeToString(lap_ms_sec, lap_min);
    lap_ms_sec = 0, lap_min = 0;

    return "Круг: " + QString::number(lap) + ", Время: " + lap_time;
}

void Stopwatch::Execute(bool checked)
{
    if(checked){
        timer->start(100);
    }
    else{
        timer->stop();
    }
}


