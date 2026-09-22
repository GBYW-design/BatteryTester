#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include"homepage.h"
#include"testpage.h"
#include"datapage.h"
#include"settingpage.h"
#include"alarmpage.h"
#include"communicationpage.h"
#include"batterytestmanager.h"
#include"modbusdevice.h"
#include"serialportmanager.h"
#include"databasemanager.h"

#include<QListwidget>
#include <QMainWindow>
#include<QStackedWidget>
#include<QAction>
#include<QLabel>
#include <QThread>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    QStackedWidget*stack;
    QListWidget*navList;
    HomePage*homePage;
    TestPage*testPage;
    DataPage*dataPage;
    AlarmPage*alarmPage;
    CommunicationPage*communicationPage;
    SettingPage*settingPage;

    QAction*openAction;
    QAction*exitAction;
    QAction*startTestAction;
    Ui::MainWindow *ui;

    void creatMenu();
    void creatToolBar();
    void creatStatusBar();
    void creatPages();
    void creatManager();
    void creatConnect();

    BatteryTestManager*testManager;
    ModbusDevice*modbusDevice;
    SerialPortManager*serialManager;
    QLabel *serialStatus;
    QLabel *deviceStatus;
    QLabel *testStatus;
    DatabaseManager*databaseManager;
    QThread *workerThread;
};
#endif // MAINWINDOW_H
