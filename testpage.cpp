#include "testpage.h"

#include <QGridLayout>
#include <QHBoxLayout>
#include <QGroupBox>

TestPage::TestPage(QWidget *parent)
    : QWidget{parent}
{
    QVBoxLayout *mainLayout=new QVBoxLayout(this);

    QGroupBox *infoBox=new QGroupBox("测试信息");
    QGridLayout *tableLayout=new QGridLayout(infoBox);
    QLabel *idLabel=new QLabel("测试编号:");
    testIdEdit=new QLineEdit();
    QLabel *modelLabel=new QLabel("电池型号:");
    batteryModelEdit=new QLineEdit();
    tableLayout->addWidget(idLabel,0,0);
    tableLayout->addWidget(testIdEdit,0,1);
    tableLayout->addWidget(modelLabel,1,0);
    tableLayout->addWidget(batteryModelEdit,1,1);
    mainLayout->addWidget(infoBox);

    QGroupBox *dataBox=new QGroupBox("实时数据");
    QGridLayout *dataLayout=new QGridLayout(dataBox);
    voltageLabel=new QLabel("0 V");
    currentLabel=new QLabel("0 A");
    temperatureLabel=new QLabel("0 ℃");
    socLabel=new QLabel("0 %");
    dataLayout->addWidget(new QLabel("电压:"),0,0);
    dataLayout->addWidget(voltageLabel,0,1);
    dataLayout->addWidget(new QLabel("电流:"),1,0);
    dataLayout->addWidget(currentLabel,1,1);
    dataLayout->addWidget(new QLabel("温度:"),2,0);
    dataLayout->addWidget(temperatureLabel,2,1);
    dataLayout->addWidget(new QLabel("SOC:"),3,0);
    dataLayout->addWidget(socLabel,3,1);
    mainLayout->addWidget(dataBox);

    QGroupBox *controlBox=new QGroupBox("测试控制");
    QHBoxLayout *buttonLayout=new QHBoxLayout(controlBox);
    startButton=new QPushButton("开始测试");
    stopButton=new QPushButton("停止测试");
    buttonLayout->addWidget(startButton);
    buttonLayout->addWidget(stopButton);
    mainLayout->addWidget(controlBox);

    QGroupBox *chartBox=new QGroupBox("实时曲线");
    QVBoxLayout *chartLayout=new QVBoxLayout(chartBox);
    voltageSeries=new QLineSeries();
    voltageSeries->setName("电压");
    currentSeries=new QLineSeries();
    currentSeries->setName("电流");
    temperatureSeries=new QLineSeries();
    temperatureSeries->setName("温度");
    QChart *chart=new QChart();
    chart->addSeries(voltageSeries);
    chart->addSeries(currentSeries);
    chart->addSeries(temperatureSeries);
    chart->setTitle("电池实时数据");
    chart->createDefaultAxes();
    chart->axes(Qt::Horizontal).first()->setTitleText("时间");
    chart->axes(Qt::Vertical).first()->setTitleText("数值");
    chartView=new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartLayout->addWidget(chartView);
    mainLayout->addWidget(chartBox);
    timeCount=0;

    connect(startButton,&QPushButton::clicked,this,&TestPage::onStartClicked);
    connect(stopButton,&QPushButton::clicked,this,&TestPage::stopTest);
}

void TestPage::onStartClicked(){
    QString testId=testIdEdit->text().trimmed();
    QString batteryModel=batteryModelEdit->text().trimmed();
    if(testId.isEmpty() || batteryModel.isEmpty()){
        return;
    }
    clearChart();
    emit startTest(testId,batteryModel);
}

void TestPage::updataBatteryData(const BatteryData &data){
    voltageLabel->setText(QString::number(data.voltage)+" V");
    currentLabel->setText(QString::number(data.current)+" A");
    temperatureLabel->setText(QString::number(data.temperature)+" ℃");
    socLabel->setText(QString::number(data.soc)+" %");

    voltageSeries->append(timeCount,data.voltage);
    currentSeries->append(timeCount,data.current);
    temperatureSeries->append(timeCount,data.temperature);
    timeCount++;
}

void TestPage::clearChart(){
    voltageSeries->clear();
    currentSeries->clear();
    temperatureSeries->clear();
    timeCount=0;
}