#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QGroupBox>

#include "batterydata.h"

class HomePage : public QWidget
{
    Q_OBJECT
public:
    explicit HomePage(QWidget *parent=nullptr);

public slots:
    void updateBatteryData(const BatteryData &data);
    void updateTestStatus(QString status);

private:
    QLabel *systemLabel;
    QLabel *testStatusLabel;
    QLabel *voltageLabel;
    QLabel *currentLabel;
    QLabel *temperatureLabel;
    QLabel *socLabel;
};


#endif // HOMEPAGE_H