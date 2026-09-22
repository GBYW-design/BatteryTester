#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<QHBoxLayout>
#include<QMenuBar>
#include<QToolBar>
#include<QStatusBar>
#include<QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(1200,800);
    setWindowTitle("电池测试系统");

    creatManager();
    creatPages();
    creatMenu();
    creatToolBar();
    creatStatusBar();
    creatConnect();
}

void MainWindow:: creatManager(){
    workerThread = new QThread(this);

    databaseManager = new DatabaseManager();
    serialManager = new SerialPortManager();
    modbusDevice = new ModbusDevice(serialManager);
    testManager = new BatteryTestManager(modbusDevice, databaseManager);

    databaseManager->moveToThread(workerThread);
    serialManager->moveToThread(workerThread);
    modbusDevice->moveToThread(workerThread);
    testManager->moveToThread(workerThread);
    connect(workerThread, &QThread::started, databaseManager, [=](){
        databaseManager->openDatabase();
        databaseManager->createTable();
    });

    workerThread->start();
}

void MainWindow::creatPages(){
    stack=new QStackedWidget(this);
    homePage=new HomePage(this);
    testPage=new TestPage(this);
    dataPage=new DataPage(databaseManager,this);
    alarmPage=new AlarmPage(this);
    communicationPage=new CommunicationPage(serialManager,this);
    settingPage=new SettingPage(this);
    stack->addWidget(homePage);
    stack->addWidget(testPage);
    stack->addWidget(dataPage);
    stack->addWidget(alarmPage);
    stack->addWidget(communicationPage);
    stack->addWidget(settingPage);

    navList=new QListWidget(this);
    navList->setFixedWidth(180);
    navList->addItem("首页");
    navList->addItem("测试");
    navList->addItem("数据");
    navList->addItem("警报");
    navList->addItem("通信");
    navList->addItem("设置");

    QWidget*central=new QWidget(this);
    setCentralWidget(central);
    QHBoxLayout*layout=new QHBoxLayout(central);
    layout->addWidget(navList);
    layout->addWidget(stack);

    connect(navList,&QListWidget::currentRowChanged,stack,&QStackedWidget::setCurrentIndex);
    navList->setCurrentRow(0);
}

void MainWindow::creatConnect(){
    connect(testPage,&TestPage::startTest,testManager,&BatteryTestManager::startTest);
    connect(testPage,&TestPage::stopTest,testManager,&BatteryTestManager::stopTest);
    connect(testManager,&BatteryTestManager::batteryDataUpdated,testPage,&TestPage::updataBatteryData);
    connect(testManager,&BatteryTestManager::batteryDataUpdated,alarmPage,&AlarmPage::checkBatteryData);
    connect(testManager,&BatteryTestManager::batteryDataUpdated,homePage,&HomePage::updateBatteryData);
    connect(testManager,&BatteryTestManager::testStatusChanged,homePage,&HomePage::updateTestStatus);
    connect(serialManager, &SerialPortManager::connectionStateChanged, this, [=](bool success){
        if(success){
            serialStatus->setText("串口: 已连接");
        }else{
            serialStatus->setText("串口: 未连接");
            deviceStatus->setText("设备: 未连接");
        }
    });
    connect(testManager,&BatteryTestManager::testStatusChanged,this,[=](QString status){
        testStatus->setText("测试:"+status);
    });
    connect(testManager,&BatteryTestManager::batteryDataUpdated,this,[=](const BatteryData &data){
        deviceStatus->setText("设备: 在线");
    });
    connect(startTestAction,&QAction::triggered,this,[=](){
        stack->setCurrentWidget(testPage);
    });

    connect(communicationPage, &CommunicationPage::scanPortRequested, serialManager, &SerialPortManager::scanPort);
    connect(serialManager, &SerialPortManager::portsScanned, communicationPage, &CommunicationPage::updatePortList);
    connect(communicationPage, &CommunicationPage::openPortRequested, serialManager, &SerialPortManager::openPort);
    connect(communicationPage, &CommunicationPage::closePortRequested, serialManager, &SerialPortManager::closePort);
    connect(dataPage, &DataPage::refreshRequested, databaseManager, &DatabaseManager::queryTestRecords);
    connect(dataPage, &DataPage::batteryDataRequested, databaseManager, &DatabaseManager::queryBatteryData);
    connect(databaseManager, &DatabaseManager::testRecordsReady, dataPage, &DataPage::updateRecordTable);
    connect(databaseManager, &DatabaseManager::batteryDataReady, dataPage, &DataPage::updateDataTable);
}

void MainWindow::creatMenu(){
    QMenu*fileMenu=menuBar()->addMenu("文件");
    openAction=new QAction("加载配置",this);
    exitAction=new QAction("退出",this);
    fileMenu->addAction(openAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);
    connect(exitAction,&QAction::triggered,this,&QWidget::close);
    connect(openAction,&QAction::triggered,this,[=](){
        settingPage->loadSetting();
    });
}

void MainWindow::creatToolBar(){
    QToolBar*toolbar=addToolBar("工具栏");
    startTestAction = new QAction("开始测试", this);
    toolbar->addAction(startTestAction);
}

void MainWindow::creatStatusBar(){
    serialStatus =new QLabel("串口未连接");
    deviceStatus=new QLabel("设备: 未连接");
    testStatus=new QLabel("测试: 空闲");
    statusBar()->addWidget(serialStatus);
    statusBar()->addWidget(deviceStatus);
    statusBar()->addWidget(testStatus);
}


MainWindow::~MainWindow()
{
    if(workerThread && workerThread->isRunning()){
        workerThread->quit();
        workerThread->wait(3000);
    }
    delete ui;
}
