#include "sqliteDataBase.h"
#include <sqlite3.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <cstring>
using namespace std;



stdSqliteDataBase::stdSqliteDataBase() : m_db(nullptr)
{
}
stdSqliteDataBase::~stdSqliteDataBase()
{
}

///// is连接数据库
bool stdSqliteDataBase::connectDB(const std::string &dbFileName)
{
    // 连接数据库

    int ret = sqlite3_open(dbFileName.c_str(), &m_db);
    if (ret != SQLITE_OK)
    {
        cout << "sqlite3 open error" << sqlite3_errmsg(m_db) << endl;
        return false;
    }
    return true;
}

/////// 执行sql语句
bool stdSqliteDataBase::execute(const std::string &sql)
{
    int ret = sqlite3_exec(m_db, sql.c_str(), NULL, NULL, NULL);
    if (ret != SQLITE_OK)
    {
        cout << "sqlite3 open error" << sqlite3_errmsg(m_db) << endl;
        return false;
    }
    return true;
}

/////// 查询sql语句
std::vector<vector<string>> stdSqliteDataBase::query(const std::string &sql)
{
    std::vector<vector<string>> data;
    char **result = NULL;
    int Row = 0;
    int Column = 0;
    int ret = sqlite3_get_table(m_db, sql.c_str(), &result, &Row, &Column, NULL);
    if (ret != SQLITE_OK)
  {
    cout << "sqlite3_get_table error" << sqlite3_errmsg(m_db) << endl;
  return data;
  }
  for (int row = 1; row <= Row; row++)
  {
    vector<string> rowData;
    for (int col = 0; col < Column; col++)
    {
      // cout << left << setw(16) << result[row * Column + col];
      rowData.push_back(result[row * Column + col]);
    }
   data.push_back(rowData);
  }

  return data;
}


 void stdSqliteDataBase::closeDB   ()
 {
  sqlite3_close(m_db);
 }

