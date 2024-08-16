#ifndef __MYSQL_DATABASE_H__
#define __MYSQL_DATABASE_H__
#include "stdDataBase.h"
#include <mysql/mysql.h>

class stdMysqlDatabase  : public stdDataBase
{
private:
MYSQL * m_sqldb;
    /* data */
public:
    stdMysqlDatabase();
    ~stdMysqlDatabase();

public:
//is连接数据库
 bool connectDB(const std::string & dbFileName);
//执行sql语句
 bool execute(const std::string sql);
//查询sql语句
 std::vector<vector<string>> query( const std::string sql) ;

 void closeDB   ();

};


#endif // !__MYSQL_DATABASE_H__