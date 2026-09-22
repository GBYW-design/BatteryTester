#include "alarmpage.h"

#include <QVBoxLayout>
#include <QDateTime>
#include <QHeaderView>



AlarmPage::AlarmPage(QWidget *parent)
    : QWidget{parent}
{
    QVBoxLayout *mainLayout=new QVBoxLayout(this);
    statusLabel=new QLabel("系统状态: 正常");
    alarmTable=new QTableWidget();
    alarmTable->setColumnCount(4);
    alarmTable->setHorizontalHeaderLabels({"时间","报警类型","当前值","等级"});
    alarmTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    mainLayout->addWidget(statusLabel);
    mainLayout->addWidget(alarmTable);

    maxTemperature=60.0;
    minVoltage=3.0;
    maxVoltage=4.2;
    minSoc=5.0;
}

void AlarmPage::checkBatteryData(const BatteryData &data){
    bool alarm=false;
    if(data.voltage<minVoltage ||data.voltage>maxVoltage){
        addAlarm("电压异常",QString::number(data.voltage)+" V","警告");
        alarm=true;
    }

    if(data.temperature>maxTemperature){
        addAlarm("温度过高", QString::number(data.temperature)+" ℃","严重");
        alarm=true;
    }

    if(data.soc<minSoc){
        addAlarm("SOC过低",QString::number(data.soc)+" %","警告");
        alarm=true;
    }

    if(alarm){
        statusLabel->setText("系统状态: 报警");
    }else{
        statusLabel->setText("系统状态: 正常");
    }
}

void AlarmPage::addAlarm(QString type,QString value,QString level){
    int row=alarmTable->rowCount();
    alarmTable->insertRow(row);
    alarmTable->setItem(row,0,new QTableWidgetItem(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")));
    alarmTable->setItem(row,1,new QTableWidgetItem(type));
    alarmTable->setItem(row,2,new QTableWidgetItem(value));
    alarmTable->setItem(row,3,new QTableWidgetItem(level));

}