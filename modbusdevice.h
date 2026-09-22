#ifndef MODBUSDEVICE_H
#define MODBUSDEVICE_H

#include"serialportmanager.h"
#include"modbusrtu.h"

#include <QObject>

class ModbusDevice : public QObject
{
    Q_OBJECT
public:
    explicit ModbusDevice(SerialPortManager*serialManager,QObject *parent = nullptr);
public slots:
  void  readBatteryData();
private slots:
  void onDataReceive(QByteArray data);
signals:
  void batteryDataReceive(QVector<quint16>values);
private:
  SerialPortManager*serialManager;
};

#endif // MODBUSDEVICE_H
