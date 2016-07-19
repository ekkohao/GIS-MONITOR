#include "dbcon.h"
#include <QString>
#include <QStringList>
#include <QtSql>
#include <QDebug>

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
    db.close();
}
bool dbcon::open()
{
    isopen=db.open();
    return isopen;
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
