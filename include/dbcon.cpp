#include "dbcon.h"
#include <QString>
#include <QStringList>
#include <QtSql>
#include <QDebug>

//#define DB_HOST "localhost"
//#define DB_NAME "gis-database"
//#define DB_USER "root"
//#define DB_PASSWD ""

#define DB_HOST "rm-bp1bv2p9m6x3n8fc1.mysql.rds.aliyuncs.com"
#define DB_NAME "rho93hp8qb"
#define DB_USER "rho93hp8qb"
#define DB_PASSWD "HFkeding1994"

dbcon::dbcon():isopen(false)
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(DB_HOST);
    db.setDatabaseName(DB_NAME);
    db.setUserName(DB_USER);
    db.setPassword(DB_PASSWD);
    db.setPort(3306);
    open();
}
dbcon::~dbcon()
{
    close();
}
bool dbcon::open()
{
    isopen=db.open();
    return isopen;
}
void dbcon::close()
{
    isopen=false;
    db.close();
}
bool dbcon::get_phonenumbers(QStringList &phoneNumberList)
{
    QSqlQuery query;
    phoneNumberList.clear();
    queries="SELECT user_phone FROM users WHERE is_send=1";
    query.exec(queries);
    while (query.next()) {
        phoneNumberList.append(query.value(0).toString());
    }
	return !phoneNumberList.isEmpty();
}

int dbcon::get_dev_id(QString devNum)
{
    QSqlQuery query;
    queries="SELECT dev_id FROM devs WHERE dev_number="+devNum;
    query.exec(queries);
    int devId=0;
    while (query.next()) {
        devId=query.value(0).toInt();
    }
    return devId;
}

void dbcon::insert_alarm(AlarmInfo &alarm,int flag)
{
    QSqlQuery query;
    QString QStraction;
    QStraction=(flag==1)?"alarms":"histories";
    queries=QString("INSERT INTO %1(action_time,action_num,i_num,tem,hum,dev_id) VALUES('%2',%3,%4,%5,%6,%7)").arg(QStraction,alarm.time,QString::number(alarm.actionCount),QString::number(alarm.iNum),alarm.tem,alarm.hum,QString::number(alarm.devId));
    query.exec(queries);
}
