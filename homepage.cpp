#include "homepage.h"

HomePage::HomePage(QWidget *parent)
    : QWidget{parent}
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    systemLabel = new QLabel("电池测试系统");
    systemLabel->setAlignment(Qt::AlignCenter);

    QGroupBox *statusBox = new QGroupBox("系统状态");
    QVBoxLayout *statusLayout = new QVBoxLayout(statusBox);

    testStatusLabel = new QLabel("测试状态: 空闲");
    statusLayout->addWidget(testStatusLabel);

    QGroupBox *dataBox = new QGroupBox("最新电池数据");
    QVBoxLayout *dataLayout = new QVBoxLayout(dataBox);

    voltageLabel = new QLabel("电压: 0 V");
    currentLabel = new QLabel("电流: 0 A");
    temperatureLabel = new QLabel("温度: 0 ℃");
    socLabel = new QLabel("SOC: 0 %");

    dataLayout->addWidget(voltageLabel);
    dataLayout->addWidget(currentLabel);
    dataLayout->addWidget(temperatureLabel);
    dataLayout->addWidget(socLabel);

    mainLayout->addWidget(systemLabel);
    mainLayout->addWidget(statusBox);
    mainLayout->addWidget(dataBox);
    mainLayout->addStretch();
}

void HomePage::updateBatteryData(const BatteryData &data){
    voltageLabel->setText("电压: " + QString::number(data.voltage) + " V");
    currentLabel->setText("电流: " + QString::number(data.current) + " A");
    temperatureLabel->setText("温度: " + QString::number(data.temperature) + " ℃");
    socLabel->setText("SOC: " + QString::number(data.soc) + " %");
}

void HomePage::updateTestStatus(QString status){
    testStatusLabel->setText("测试状态: " + status);
}