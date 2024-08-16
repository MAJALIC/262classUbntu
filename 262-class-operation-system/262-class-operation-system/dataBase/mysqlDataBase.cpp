#include "mysqlDataBase.h"
#include <sqlite3.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <cstring>
using namespace std;


stdMysqlDatabase::stdMysqlDatabase() : m_sqldb(nullptr)
{
}
stdMysqlDatabase::~stdMysqlDatabase()
{
  closeDB   ();
}

///// is连接数据库
bool stdMysqlDatabase::connectDB(const std::string &basename)
{
    // 连接数据库
  // 连接数据库
  m_sqldb = mysql_init(NULL);
  if (m_sqldb == nullptr)
  {
    cout << "mysql failed" << endl;
    exit(-1);
  }
  cout << "初始化成功" << endl;
  const char *host = "localhost";
  const char *user = "debian-sys-maint";
  const char *passwd = "nssDid0hHwFRgX3P";
  const char *mybaseName = basename.c_str();
  int port = 3306;
  if (mysql_real_connect(m_sqldb, host, user, passwd, mybaseName, port, NULL, 0) == NULL)
  {
    cout << " connect mysql server error" << endl;
    return false;
  }

    return true;
}

/////// 执行sql语句
bool stdMysqlDatabase::execute(const std::string sql)
{
  const char *msql = sql.c_str();
  int ret = mysql_query(m_sqldb, msql);
  if (ret != 0)
  {
    cout << "mysql_query error.1"<< mysql_error(m_sqldb) << endl;
    return false;
  }
  cout << "连接数据库成功" <<endl;
  return true;
}

/////// 查询sql语句
std::vector<vector<string>> stdMysqlDatabase::query(const std::string sql)
{
vector<vector<string>> Data;

 if (execute(sql)==false)
 {
  return Data;
 }
  // 结果集
  MYSQL_RES *result = mysql_store_result(m_sqldb);
  if (result == NULL)
  {
    cout << "mysql_store_result error." << mysql_error(m_sqldb) << endl;
     return Data;
  }

  // 获取结果集的列数
  unsigned int cols = mysql_num_fields(result);

    vector<string> rowData;
  //获取数据
  MYSQL_ROW row;
  while((row = mysql_fetch_row(result)) != NULL)
  {
    //每个row变量表示是一行
    for (int col = 0; col < cols; col++)
    {
     rowData.push_back(row[col])  ;
    }
    Data.push_back(rowData);
  }

  //释放结果集
  mysql_free_result(result);

  return Data;
}


 void stdMysqlDatabase::closeDB   ()
 {
      if(m_sqldb!=NULL){
    mysql_close(m_sqldb);
    m_sqldb =NULL;}
 }

