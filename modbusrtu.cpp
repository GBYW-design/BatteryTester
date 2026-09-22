#include "modbusrtu.h"

ModbusRTU::ModbusRTU(QObject *parent)
    : QObject{parent}
{

}

QByteArray ModbusRTU::createReadRequest(quint8 slave,quint16 address,quint16 count){
    QByteArray frame;
    frame.append(char(slave));
    frame.append(char(0x03));
    frame.append(char(address>>8));
    frame.append(char(address&0xff));
    frame.append(char(count>>8));
    frame.append(char(count&0xff));
    quint16 crc =crc16(frame);
    frame.append(char(crc & 0xff));
    frame.append(char(crc >> 8));
    return frame;
}

quint16 ModbusRTU::crc16(QByteArray data){
    quint16 crc=0xffff;
    for(char c:data){
        crc^=(quint8)c;
        for(int i=0;i<8;i++){
            if(crc&0x0001){
                crc>>=1;
                crc^=0xA001;
            }
            else{
                crc>>=1;
            }
        }
    }
    return crc;
}

bool ModbusRTU:: parseReadResponse(QByteArray frame,QVector<quint16>&values){
    if(frame.size()<5){
        return false;
    }
    QByteArray data=frame.left(frame.size()-2);
    quint16 crc=crc16(data);
    quint16 recrc=(quint8)frame[frame.size()-2]
                    |(quint8)frame[frame.size()-1]<<8;
    if(crc!=recrc){
        return false;
    }
    if((quint8)frame[1]!=0x03){
        return false;
    }
    quint8 byteCount=(quint8)frame[2];
    if(frame.size()!=byteCount+5){
        return false;
    }
    for(int i=0;i<byteCount;i+=2){
        quint16 value=((quint8)frame[3+i]<<8)
        |
        (quint8)frame[4+i];
        values.append(value);
    }
    return true;
}