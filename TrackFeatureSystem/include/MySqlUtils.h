#ifndef MYSQLUTILS_H
#define MYSQLUTILS_H

#include <QSqlDatabase>
#include <QSql>
#include <QSqlQuery>

class Q_DECL_EXPORT MySqlUtils
{
public:
    MySqlUtils();
public:
    //获取连接
    static QSqlDatabase getConnection();
    //关闭连接
    static void release(QSqlDatabase db);
};

#endif // MYSQLUTILS_H
