#ifndef _DBCON_H_
#define _DBCON_H_
#include <QString>
#include <QStringList>
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
    /*获取需要发送的手机号列表，无返回flase*/
    bool get_phonenumbers(QStringList &phoneNumberList);
    /*获取设备id无返回0*/
    int get_dev_id(QString devNum);
    void insert_alarm(AlarmInfo &alarm,int flag);
    /*保存数据库是否链接的状态*/
    bool isopen;
private:
    /*保存查询语句*/
    QString queries;
    /*数据库句柄*/
    QSqlDatabase db;
};

#endif // _DBCON_H_
