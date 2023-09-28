#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <QObject>
#include <QTimer>

class Stopwatch : public QObject
{
    Q_OBJECT
public:
    explicit Stopwatch(QObject *parent = nullptr);

    void pb_lap_pressed();

    void Counting();

    void Clear();

    QString GetTime();

    QString GetLapTime();

    QString TimeToString(double ms_sec, int min);

    void Execute(bool checked);

signals:
    void sig_pb_lap_pressed();

    void sig_start_toggled();

private:
    double ms_sec = 0.0;
    int min = 0;
    QString time = "00:00.0";

    int lap = 0;
    double lap_ms_sec = 0.0;
    int lap_min = 0;
    QString lap_time = "00:00.0";

    QString str_0;

    QTimer *timer;
};

#endif // STOPWATCH_H
