#ifndef __SQLITEDATABASE_H__
#define __SQLITEDATABASE_H__
#include "stdDataBase.h"
#include <sqlite3.h>

class stdSqliteDataBase  : public stdDataBase
{

public:
    stdSqliteDataBase ();
    ~stdSqliteDataBase();

public:
//is连接数据库
 bool connectDB(const std::string & dbFileName);
//执行sql语句
 bool execute(const std::string &sql);
//查询sql语句
 std::vector<vector<string>> query( const std::string &sql) ;

 void closeDB();
private:
sqlite3 * m_db;
    /* data */
};




#endif // !__SQLITEDATABASE_H__

