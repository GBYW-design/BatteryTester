#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include "batterydata.h"

#include <QList>
#include <QVariantMap>
#include <QObject>
#include<QSqlDatabase>
#include <QDateTime>

class DatabaseManager : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseManager(QObject *parent = nullptr);
public slots:
    bool openDatabase();
    bool createTable();
    int insertTestRecord(QString testId,QString batteryModel,QDateTime startTime);
    bool insertBatteryData(int recordId,QDateTime time,const BatteryData &data);
    bool finishTestRecord(int recordId,QDateTime endTime,QString result);
    void queryTestRecords();
    void queryBatteryData(int recordId);
signals:
    void testRecordsReady(QList<QVariantMap> records);
    void batteryDataReady(QList<QVariantMap> datas);
private:
    QSqlDatabase db;
};

#endif // DATABASEMANAGER_H
