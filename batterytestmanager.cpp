#include "batterytestmanager.h"
#include<QDebug>
BatteryTestManager::BatteryTestManager(ModbusDevice*device,DatabaseManager *databaseManager,QObject *parent)
    : QObject{parent},device(device),databaseManager(databaseManager)
{
    timer=new QTimer(this);
    connect(timer,&QTimer::timeout,device,&ModbusDevice::readBatteryData);
    connect(device,&ModbusDevice::batteryDataReceive,this,&BatteryTestManager::onBatteryDataReceived);
}

void BatteryTestManager::startTest(QString testId,QString batteryModel){
    if(testing){
        qDebug()<<"当前已经在测试中";
        return;
    }
    currentTestId=testId;
    currentBatteryModel=batteryModel;
    startTime=QDateTime::currentDateTime();
    if(databaseManager==nullptr){
        qDebug()<<"数据库管理器为空";
        return;
    }
    currentRecordId=databaseManager->insertTestRecord(
        currentTestId,
        currentBatteryModel,
        startTime
        );

    if(currentRecordId<0){
        qDebug()<<"测试记录创建失败";
        return;
    }
    testing=true;
    qDebug()<<"编号:"<<currentTestId;
    qDebug()<<"型号:"<<currentBatteryModel;
    qDebug()<<"记录ID:"<<currentRecordId;
    emit testStarted();
    emit testStatusChanged("测试运行中");
    device->readBatteryData();
    timer->start(1000);
}

void BatteryTestManager::stopTest(){
    if(!testing){
        return;
    }
    testing=false;
    emit testStatusChanged("测试停止");
    timer->stop();
    if(databaseManager!=nullptr&&currentRecordId>=0){
        bool success=databaseManager->finishTestRecord(
            currentRecordId,
            QDateTime::currentDateTime(),
            "STOPPED"
            );

        if(!success){
            qDebug()<<"测试记录更新失败";
        }
    }
    qDebug()<<"测试停止";
    currentRecordId=-1;
    emit testStoped();
}

void BatteryTestManager:: onBatteryDataReceived(QVector<quint16> values){
    if(!testing){
        return;
    }
    if(values.size()<4){
        return;
    }
    data.voltage =values[0]/1000.0;
    data.current =values[1]/100.0;
    data.temperature =values[2]/10.0;
    data.soc =values[3]/10.0;
    if(databaseManager!=nullptr&&currentRecordId>=0){
        bool success=databaseManager->insertBatteryData(
            currentRecordId,
            QDateTime::currentDateTime(),
            data
            );
        if(!success){
            qDebug()<<"采样数据保存失败";
        }
    }
    emit batteryDataUpdated(data);
}