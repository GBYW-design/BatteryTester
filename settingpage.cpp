#include "settingpage.h"

#include <QVBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QSettings>
#include <QMessageBox>

SettingPage::SettingPage(QWidget *parent)
    : QWidget{parent}
{
    QVBoxLayout *mainLayout=new QVBoxLayout(this);
    QGroupBox *serialBox=new QGroupBox("串口默认参数");
    QGridLayout *serialLayout=new QGridLayout(serialBox);
    QLabel *baudLabel=new QLabel("波特率:");
    baudRateBox=new QComboBox();
    baudRateBox->addItem("9600");
    baudRateBox->addItem("19200");
    baudRateBox->addItem("38400");
    baudRateBox->addItem("115200");
    QLabel *slaveLabel=new QLabel("从站地址:");
    slaveAddressEdit=new QLineEdit();

    serialLayout->addWidget(baudLabel,0,0);
    serialLayout->addWidget(baudRateBox,0,1);
    serialLayout->addWidget(slaveLabel,1,0);
    serialLayout->addWidget(slaveAddressEdit,1,1);
    mainLayout->addWidget(serialBox);

    QGroupBox *alarmBox=new QGroupBox("电池报警阈值");
    QGridLayout *alarmLayout=new QGridLayout(alarmBox);
    QLabel *tempLabel=new QLabel("最大温度:");
    maxTemperatureEdit=new QLineEdit();
    QLabel *voltageLabel=new QLabel("最低电压:");
    minVoltageEdit=new QLineEdit();

    alarmLayout->addWidget(tempLabel,0,0);
    alarmLayout->addWidget(maxTemperatureEdit,0,1);
    alarmLayout->addWidget(voltageLabel,1,0);
    alarmLayout->addWidget(minVoltageEdit,1,1);
    mainLayout->addWidget(alarmBox);

    saveButton=new QPushButton("保存配置");
    mainLayout->addWidget(saveButton);

    mainLayout->addStretch();
    loadSetting();
    connect(saveButton,&QPushButton::clicked,this,&SettingPage::saveSetting);
}

void SettingPage::loadSetting(){
    QSettings settings("BatteryTester","BatterySystem");

    QString baud=settings.value("Serial/BaudRate","9600").toString();
    baudRateBox->setCurrentText(baud);

    QString slave=settings.value("Serial/SlaveAddress","1").toString();
    slaveAddressEdit->setText(slave);

    QString maxTemp=settings.value("Alarm/MaxTemperature","60").toString();
    maxTemperatureEdit->setText(maxTemp);

    QString minVoltage=settings.value("Alarm/MinVoltage","3.0").toString();
    minVoltageEdit->setText(minVoltage);
}

void SettingPage::saveSetting(){
    QSettings settings("BatteryTester","BatterySystem");

    settings.setValue("Serial/BaudRate",baudRateBox->currentText());
    settings.setValue("Serial/SlaveAddress",slaveAddressEdit->text());
    settings.setValue("Alarm/MaxTemperature",maxTemperatureEdit->text());
    settings.setValue("Alarm/MinVoltage",minVoltageEdit->text());

    settings.sync();
    QMessageBox::information(this,"提示","配置保存成功");
}