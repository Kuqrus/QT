#include "stopwatch.h"

Stopwatch::Stopwatch(QObject *parent)
    : QObject{parent}
{

}

void Stopwatch::pb_lap_pressed()
{
    emit sig_pb_lap_pressed();
}

void Stopwatch::Stopwatching()
{
    if(ms >= 9){
        sec++;
        ms = 0;
    }
    else if(sec >= 59){
        min++;
        sec = 0;
    }
    else ms++;


    if(min <= 9){
        time = "0" + QString::number(min);
    }
    else{
        time = QString::number(min);
    }

    if(sec <= 9){
        time += ":0" + QString::number(sec);
    }
    else{
        time += ":" + QString::number(sec);
    }

    time += "." + QString::number(ms);
}

void Stopwatch::Clear()
{
    ms = 0, sec = 0, min = 0;
    lap = 0;
    time = "00:00.0";
}

QString Stopwatch::GetTime()
{
    return time;
}

QString Stopwatch::GetLapTime()
{
    lap++;
    return "Круг: " + QString::number(lap) + ", Время: " + time;
}
