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

    void Stopwatching();

    void Clear();

    QString GetTime();

    QString GetLapTime();

signals:
    void sig_pb_lap_pressed();

private:
    int ms = 0;
    int sec = 0;
    int min = 0;

    int lap = 0;

    QString time = "00:00.0";
};

#endif // STOPWATCH_H
