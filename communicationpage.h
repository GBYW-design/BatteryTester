#ifndef COMMUNICATIONPAGE_H
#define COMMUNICATIONPAGE_H

#include"serialportmanager.h"
#include <QWidget>
#include <QComboBox>
#include <QPushButton>
#include<QLabel>
#include<QTextEdit>
#include <QGroupBox>
#include <QGridLayout>

class CommunicationPage : public QWidget
{
    Q_OBJECT
public:
    explicit CommunicationPage(SerialPortManager*serialManager,QWidget *parent = nullptr);
public slots:
    void scanPorts();
    void openPort();
    void closePort();
    void updatePortList(QStringList ports);
signals:
    void scanPortRequested();
    void openPortRequested(QString port, int baudRate);
    void closePortRequested();
private:
    SerialPortManager*serialManager;
    QComboBox *portBox;
    QComboBox *baudBox;
    QPushButton *scanButton;
    QPushButton *openButton;
    QPushButton *closeButton;
};

#endif
