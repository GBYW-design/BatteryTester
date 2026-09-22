#ifndef SERIALPORTMANAGER_H
#define SERIALPORTMANAGER_H

#include <QObject>
#include<QSerialPort>
#include<QSerialPortInfo>
#include<QStringList>

class SerialPortManager : public QObject
{
    Q_OBJECT
public:
    explicit SerialPortManager(QObject *parent = nullptr);

public slots:
    QStringList scanPort();
    bool isOpen();
    bool openPort(const QString portName,int baudRate);
    bool closePort();
    void sendData(const QByteArray& data);
private slots:
    void readData();

signals:
    void dataReceive(QByteArray data);
    void connectionStateChanged(bool connected);
    void errorOccurred(QString message);
    void portsScanned(QStringList ports);
private:
    QSerialPort *serial;
};

#endif // SERIALPORTMANAGER_H
