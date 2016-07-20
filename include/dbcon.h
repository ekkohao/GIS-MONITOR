#ifndef _DBCON_H_
#define _DBCON_H_
#include <QString>
#include <QStringList>
#include <QtSql>

class dbcon
{
public:
    dbcon();
    ~dbcon();
    bool open();
    void close();
    /*获取需要发送的手机号列表，无返回flase*/
	bool dbcon::get_phonenumbers(QStringList &phoneNumberList);
private:
    /*保存查询语句*/
    QString queries;
    /*数据库句柄*/
    QSqlDatabase db;
    /*保存数据库是否链接的状态*/
    bool isopen;
};

#endif // _DBCON_H_
