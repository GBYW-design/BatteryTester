#ifndef BATTERYTESTMANAGER_H
#define BATTERYTESTMANAGER_H

#include"modbusdevice.h"
#include"batterydata.h"
#include"databasemanager.h"

#include<QTimer>
#include <QObject>
#include <QDateTime>
#include <QVector>

class BatteryTestManager : public QObject
{
    Q_OBJECT
public:
    explicit BatteryTestManager(ModbusDevice *device,DatabaseManager *databaseManager,QObject *parent = nullptr);

signals:
    void batteryDataUpdated(const BatteryData &data);
    //发给ui
    void testStarted();
    void testStoped();
    void testStatusChanged(QString status);
private slots:
    void onBatteryDataReceived(QVector<quint16> values);
public slots:
    void startTest(QString testId,QString batteryModel);
    void stopTest();
private:
    BatteryData data;
    ModbusDevice*device;
    QString currentTestId;
    QString currentBatteryModel;
    bool testing=false;
    QTimer*timer;
    DatabaseManager *databaseManager;
    int currentRecordId=-1;
    QDateTime startTime;

};

#endif // BATTERYTESTMANAGER_H
