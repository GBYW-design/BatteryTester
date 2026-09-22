#ifndef SETTINGPAGE_H
#define SETTINGPAGE_H

#include <QWidget>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>

class SettingPage : public QWidget
{
    Q_OBJECT

public:
    explicit SettingPage(QWidget *parent = nullptr);
    void loadSetting();
private slots:
    void saveSetting();
private:
    QComboBox *baudRateBox;
    QLineEdit *slaveAddressEdit;
    QLineEdit *maxTemperatureEdit;
    QLineEdit *minVoltageEdit;
    QPushButton *saveButton;
};

#endif // SETTINGPAGE_H