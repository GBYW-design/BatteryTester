#include "modbusdevice.h"
#include<QDebug>
ModbusDevice::ModbusDevice(SerialPortManager *serialManager,QObject *parent )
    : QObject{parent},serialManager(serialManager)
{
    connect(serialManager,&SerialPortManager::dataReceive,this,&ModbusDevice::onDataReceive);
}


void ModbusDevice::readBatteryData(){
    QByteArray frame;
    frame=ModbusRTU::createReadRequest(1,100,4);
    serialManager->sendData(frame);
}

void ModbusDevice::onDataReceive(QByteArray data){
    QVector<quint16>values;
    bool ok=ModbusRTU::parseReadResponse(data,values);
    if(ok){
        emit batteryDataReceive(values);
    }
}
