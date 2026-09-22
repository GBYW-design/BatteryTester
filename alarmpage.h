#ifndef ALARMPAGE_H
#define ALARMPAGE_H

#include <QWidget>
#include <QTableWidget>
#include <QLabel>

#include "batterydata.h"

class AlarmPage : public QWidget
{
    Q_OBJECT
public:
    explicit AlarmPage(QWidget *parent=nullptr);

public slots:
    void checkBatteryData(const BatteryData &data);

private:
    void addAlarm(QString type,QString value,QString level);

private:
    QTableWidget *alarmTable;
    QLabel *statusLabel;
    double maxTemperature;
    double minVoltage;
    double maxVoltage;
    double minSoc;
};

#endif // ALARMPAGE_H