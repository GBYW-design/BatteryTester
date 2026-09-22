#include "databasemanager.h"

#include<QSqlQuery>
#include<QDebug>
#include<QSqlError>


DatabaseManager::DatabaseManager(QObject *parent)
    : QObject{parent}
{

}

bool DatabaseManager:: openDatabase(){
    db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("battery_test.db");
    if(!db.open()){
        qDebug()<<"数据库打开失败！";
        return false;
    }
    qDebug()<<"数据库打开成功！";
        return true;
}

bool DatabaseManager::createTable(){
    QSqlQuery query;
    QString testSql=R"(
    CREATE TABLE IF NOT EXISTS test_record(
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    test_id TEXT,
    battery_model TEXT,
    start_time TEXT,
    end_time TEXT,
    result TEXT
    )
)";
    if(!query.exec(testSql)){
        qDebug()<<"创建test_record表失败:"<<query.lastError();
        return false;
    }

    QString dataSql=R"(
        CREATE TABLE IF NOT EXISTS battery_data(
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            record_id INTEGER NOT NULL,
            time TEXT NOT NULL,
            voltage REAL,
            current REAL,
            temperature REAL,
            soc REAL
        )
    )";
    if(!query.exec(dataSql)){
        qDebug()<<"创建battery_data表失败:"<<query.lastError().text();
        return false;
    }
    return true;
}

int DatabaseManager::insertTestRecord(QString testId,QString batteryModel,QDateTime startTime){
    QSqlQuery query;
    query.prepare(R"(
        INSERT INTO test_record(
            test_id,
            battery_model,
            start_time,
            result
        )
        VALUES(
            :test_id,
            :battery_model,
            :start_time,
            :result
        )
    )");
    query.bindValue(":test_id",testId);
    query.bindValue(":battery_model",batteryModel);
    query.bindValue(":start_time",startTime.toString(Qt::ISODate));
    query.bindValue(":result","RUNNING");
    if(!query.exec()){
        qDebug()<<"插入测试记录失败:"<<query.lastError().text();
        return -1;
    }
    return query.lastInsertId().toInt();
}

bool DatabaseManager::insertBatteryData(int recordId,QDateTime time,const BatteryData &data){
    QSqlQuery query;
    query.prepare(R"(
        INSERT INTO battery_data(
            record_id,
            time,
            voltage,
            current,
            temperature,
            soc
        )
        VALUES(
            :record_id,
            :time,
            :voltage,
            :current,
            :temperature,
            :soc
        )
    )");
    query.bindValue(":record_id",recordId);
    query.bindValue(":time",time.toString(Qt::ISODate));
    query.bindValue(":voltage",data.voltage);
    query.bindValue(":current",data.current);
    query.bindValue(":temperature",data.temperature);
    query.bindValue(":soc",data.soc);
    if(!query.exec()){
        qDebug()<<"插入采样数据失败:"<<query.lastError().text();
        return false;
    }
    return true;
}

bool DatabaseManager::finishTestRecord(int recordId,QDateTime endTime,QString result){
    QSqlQuery query;
    query.prepare(R"(
        UPDATE test_record
        SET end_time=:end_time,result=:result
        WHERE id=:id
    )");
    query.bindValue(":end_time",endTime.toString(Qt::ISODate));
    query.bindValue(":result",result);
    query.bindValue(":id",recordId);
    if(!query.exec()){
        qDebug()<<"更新测试记录失败:"<<query.lastError().text();
        return false;
    }
    return true;
}

void DatabaseManager::queryTestRecords(){
    QList<QVariantMap> records;
    QSqlQuery query;
    QString sql=R"(
        SELECT
            id,
            test_id,
            battery_model,
            start_time,
            end_time,
            result
        FROM test_record
        ORDER BY id DESC
    )";
    if(!query.exec(sql)){
        qDebug()<<"查询测试记录失败:"<<query.lastError().text();
        return;
    }
    while(query.next()){
        QVariantMap record;
        record["id"]=query.value("id");
        record["test_id"]=query.value("test_id");
        record["battery_model"]=query.value("battery_model");
        record["start_time"]=query.value("start_time");
        record["end_time"]=query.value("end_time");
        record["result"]=query.value("result");
        records.append(record);
    }
    emit testRecordsReady(records);
}

void DatabaseManager::queryBatteryData(int recordId){
    QList<QVariantMap> datas;
    QSqlQuery query;
    query.prepare(R"(
        SELECT
            time,
            voltage,
            current,
            temperature,
            soc
        FROM battery_data
        WHERE record_id=:record_id
        ORDER BY id ASC
    )");
    query.bindValue(":record_id",recordId);
    if(!query.exec()){
        qDebug()<<"查询采样数据失败:"<<query.lastError().text();
        return;
    }
    while(query.next()){
        QVariantMap data;
        data["time"]=query.value("time");
        data["voltage"]=query.value("voltage");
        data["current"]=query.value("current");
        data["temperature"]=query.value("temperature");
        data["soc"]=query.value("soc");
        datas.append(data);
    }
    emit batteryDataReady(datas);
}