#ifndef _DBCON_H_
#define _DBCON_H_
#include <QString>
#include <QStringList>
#include "include/haohelp.h"
#include <QtSql>

typedef struct{
    unsigned int devId;
    QString time;
    unsigned int actionCount;
    unsigned int iNum;
    QString tem;
    QString hum;
}AlarmInfo;

class dbcon
{
public:
    dbcon();
    ~dbcon();
    bool open();
    void close();
    void reopen();
    /*获取需要发送的手机号列表，无返回flase*/
    bool get_phonenumbers(QStringList &phoneNumberList);
    /*获取设备id无返回0*/
    unsigned int get_dev(QString &devNum);
    void insert_alarm(AlarmInfo &alarm,int flag);
    /*保存数据库是否链接的状态*/
    bool isopen;
    static QString dbHost;
    static QString dbName;
    static QString dbUserName;
    static QString dbPasswd;
    static QString prefix;
private:
    /*保存查询语句*/
    QString queries;
    /*数据库句柄*/
    QSqlDatabase db;

    int group_id;
};

#endif // _DBCON_H_
