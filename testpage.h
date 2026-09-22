#ifndef TESTPAGE_H
#define TESTPAGE_H

#include"batterydata.h"

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>

class TestPage : public QWidget
{
    Q_OBJECT

public:
    explicit TestPage(QWidget *parent=nullptr);
private slots:
    void clearChart();
public slots:
    void onStartClicked();
    void updataBatteryData(const BatteryData &data);
signals:
    void startTest(QString testId,QString batteryModel);
    void stopTest();
private:
    QLineEdit *testIdEdit;
    QLineEdit *batteryModelEdit;
    QLabel *voltageLabel;
    QLabel *currentLabel;
    QLabel *temperatureLabel;
    QLabel *socLabel;
    QPushButton *startButton;
    QPushButton *stopButton;
    QChartView *chartView;
    QLineSeries *voltageSeries;
    QLineSeries *currentSeries;
    QLineSeries *temperatureSeries;
    int timeCount;
    BatteryData data;
};

#endif // TESTPAGE_H