#include "communicationpage.h"
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QGridLayout>
#include<QGroupBox>

CommunicationPage::CommunicationPage(SerialPortManager *serialManager,QWidget *parent)
    : QWidget{parent},serialManager(serialManager)
{
    portBox=new QComboBox(this);
    baudBox=new QComboBox(this);
    baudBox->addItems({"9600","19200","38400","57600","115200"});
    scanButton=new QPushButton("扫描串口");
    openButton=new QPushButton("打开");
    closeButton=new QPushButton("关闭");

    QGroupBox *configBox=new QGroupBox("串口配置");
    configBox->setFixedHeight(300);
    QGridLayout *configLayout=new QGridLayout(configBox);
    configLayout->addWidget(new QLabel("串口号:"),0,0);
    configLayout->addWidget(portBox,0,1);
    configLayout->addWidget(new QLabel("波特率:"),1,0);
    configLayout->addWidget(baudBox,1,1);

    QGroupBox *operateBox=new QGroupBox("操作");
    operateBox->setFixedHeight(200);
    QHBoxLayout *operateLayout=new QHBoxLayout(operateBox);
    operateLayout->addWidget(scanButton);
    operateLayout->addWidget(openButton);
    operateLayout->addWidget(closeButton);

    QVBoxLayout *mainLayout=new QVBoxLayout(this);
    mainLayout->addWidget(configBox);
    mainLayout->addWidget(operateBox);

    connect(scanButton,&QPushButton::clicked,this,&CommunicationPage::scanPorts);
    connect(openButton,&QPushButton::clicked,this,&CommunicationPage::openPort);
    connect(closeButton,&QPushButton::clicked,this,&CommunicationPage::closePort);
    scanPorts();
}


void CommunicationPage::scanPorts(){
     emit scanPortRequested();
}

void CommunicationPage::updatePortList(QStringList ports){
    portBox->clear();
    portBox->addItems(ports);
}

void CommunicationPage::openPort(){
    emit openPortRequested(portBox->currentText(), baudBox->currentText().toInt());
}

void CommunicationPage::closePort(){
    emit closePortRequested();
}