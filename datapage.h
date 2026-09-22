#ifndef DATAPAGE_H
#define DATAPAGE_H

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>

#include "DatabaseManager.h"

class DataPage:public QWidget
{
    Q_OBJECT
public:
    explicit DataPage(DatabaseManager *databaseManager,QWidget *parent=nullptr);
private slots:
    void refreshData();
    void showBatteryData(int row,int column);
    void setupUI();
public slots:
    void updateRecordTable(QList<QVariantMap> records);
    void updateDataTable(QList<QVariantMap> datas);
signals:
    void refreshRequested();
    void batteryDataRequested(int recordId);
private:
    DatabaseManager *databaseManager;
    QPushButton *refreshButton;
    QTableWidget *recordTable;
    QTableWidget *dataTable;
};

#endif