#include "datapage.h"
#include "databasemanager.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QTableWidgetItem>

DataPage::DataPage(DatabaseManager *databaseManager,QWidget *parent)
    : QWidget(parent),databaseManager(databaseManager)
{
    setupUI();
    connect(refreshButton,&QPushButton::clicked,this,&DataPage::refreshData);
    connect(recordTable,&QTableWidget::cellClicked, this,&DataPage::showBatteryData);
    refreshData();
}

void DataPage::setupUI(){
    refreshButton=new QPushButton("刷新数据",this);
    recordTable=new QTableWidget(this);
    recordTable->setColumnCount(6);
    QStringList headers;
    headers<<"记录ID"<<"测试编号"<<"电池型号"
            <<"开始时间"<<"结束时间"<<"测试结果";
    recordTable->setHorizontalHeaderLabels(headers);
    recordTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    recordTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    recordTable->setSelectionMode(QAbstractItemView::SingleSelection);
    recordTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    recordTable->verticalHeader()->setVisible(false);

    dataTable=new QTableWidget(this);
    dataTable->setColumnCount(5);
    QStringList dataHeaders;
    dataHeaders<<"时间"<<"电压"<<"电流"<<"温度"<<"SOC";
    dataTable->setHorizontalHeaderLabels(dataHeaders);
    dataTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    dataTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    dataTable->setSelectionMode(QAbstractItemView::SingleSelection);
    dataTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    dataTable->verticalHeader()->setVisible(false);


    QHBoxLayout *topLayout=new QHBoxLayout;
    topLayout->addWidget(refreshButton);
    topLayout->addStretch();

    QVBoxLayout *mainLayout=new QVBoxLayout(this);
    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(recordTable);
    mainLayout->addWidget(dataTable);
}

void DataPage::refreshData(){
    emit refreshRequested();
}

void DataPage::updateRecordTable(QList<QVariantMap> records){
    recordTable->setRowCount(0);
    for(const QVariantMap &record:records){
        int row=recordTable->rowCount();
        recordTable->insertRow(row);
        recordTable->setItem(row,0,new QTableWidgetItem(record["id"].toString()));
        recordTable->setItem(row,1,new QTableWidgetItem(record["test_id"].toString()));
        recordTable->setItem(row,2,new QTableWidgetItem(record["battery_model"].toString()));
        recordTable->setItem(row,3,new QTableWidgetItem(record["start_time"].toString()));
        recordTable->setItem(row,4,new QTableWidgetItem(record["end_time"].toString()));
        recordTable->setItem(row,5,new QTableWidgetItem(record["result"].toString()));
    }
}

void DataPage::showBatteryData(int row,int column){
    Q_UNUSED(column);
    QTableWidgetItem *item=recordTable->item(row,0);
    if(item==nullptr){
        return;
    }
    int recordId=item->text().toInt();
    emit batteryDataRequested(recordId);
}

void DataPage::updateDataTable(QList<QVariantMap> datas){
    dataTable->setRowCount(0);
    for(const QVariantMap &data:datas){
        int newRow=dataTable->rowCount();
        dataTable->insertRow(newRow);
        dataTable->setItem(newRow,0,new QTableWidgetItem(data["time"].toString()));
        dataTable->setItem(newRow,1,new QTableWidgetItem(data["voltage"].toString()));
        dataTable->setItem(newRow,2,new QTableWidgetItem(data["current"].toString()));
        dataTable->setItem(newRow,3,new QTableWidgetItem(data["temperature"].toString()));
        dataTable->setItem(newRow,4,new QTableWidgetItem(data["soc"].toString()));
    }
}