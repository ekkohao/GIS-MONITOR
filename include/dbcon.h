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
    /*��ȡ��Ҫ���͵��ֻ����б��޷���flase*/
	bool dbcon::get_phonenumbers(QStringList &phoneNumberList);
private:
    /*�����ѯ���*/
    QString queries;
    /*���ݿ���*/
    QSqlDatabase db;
    /*�������ݿ��Ƿ����ӵ�״̬*/
    bool isopen;
};

#endif // _DBCON_H_
