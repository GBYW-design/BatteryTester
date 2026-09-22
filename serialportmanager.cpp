#include "serialportmanager.h"
#include<QDebug>

SerialPortManager::SerialPortManager(QObject *parent)
    : QObject{parent}
{
    serial=new QSerialPort(this);
    connect(serial,&QSerialPort::readyRead,this,&SerialPortManager::readData);
}

QStringList SerialPortManager::scanPort(){
    QStringList portNames;
    const QList<QSerialPortInfo> ports=QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &port : ports){
        portNames.append(port.portName());
    }
    emit portsScanned(portNames);
    return portNames;
}

bool SerialPortManager::openPort(QString portName,int baudRate){
    if(serial->isOpen()){
        serial->close();
    }
    serial->setPortName(portName);
    serial->setBaudRate(baudRate);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);
     bool success= serial->open(QIODevice::ReadWrite);
    if(success){
         emit connectionStateChanged(true);
    }else{
        emit errorOccurred(serial->errorString());
        emit connectionStateChanged(false);
    }
    return success;
}

bool SerialPortManager::closePort(){
    if(serial->isOpen()){
        serial->close();
    }
    bool closed = !serial->isOpen();
    if(closed){
        emit connectionStateChanged(false);
    }
    return closed;
}

void SerialPortManager::sendData(const QByteArray& data){
    if(!serial->isOpen()){
        emit errorOccurred("串口未打开，无法发送数据");
        return;
    }
    qint64 result=serial->write(data);
    if(result==-1){
        emit errorOccurred(serial->errorString());
    }
}

bool SerialPortManager::isOpen(){
    return serial->isOpen();
}

void SerialPortManager::readData(){
    QByteArray data;
    data=serial->readAll();
    emit dataReceive(data);
}