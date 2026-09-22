#ifndef MODBUSRTU_H
#define MODBUSRTU_H

#include <QObject>

class ModbusRTU : public QObject
{
    Q_OBJECT
public:
    explicit ModbusRTU(QObject *parent = nullptr);
public slots:
    static QByteArray createReadRequest(quint8 slave,quint16 address,quint16 count);

    static bool parseReadResponse(QByteArray frame,QVector<quint16>& values);

private:
    static quint16 crc16(QByteArray data);


};

#endif // MODBUSRTU_H
