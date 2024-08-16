#include <iostream>
using namespace std;
#include <stdio.h>
#include <sqlite3.h>
#include <unistd.h>
#include <iomanip>
#include <vector>

void execute(sqlite3 *myDB)
{

  // 创建数据库表
  const char *sql = "CREATE TABLE IF NOT EXISTS userInfo (username text not null,passwd text not null );";

  // 执行sql语句
  int ret = sqlite3_exec(myDB, sql, NULL, NULL, NULL);
  if (ret != SQLITE_OK)
  {
    cout << "sqlite3 open error1" << sqlite3_errmsg(myDB) << endl;
    _exit(-1);
  }
#if 1
  // 插入数据
  string username;
  cout << "请输入·用户名";
  cin >> username;

  string passwd;
  cout << "请输入·用户密码";
  cin >> passwd;

  char buffer[64] = "INSERT INTO userInfo(username,passwd) VALUES ('%s',%s) ;";
  char requestSql[128] = {0};
  sprintf(requestSql, buffer, username.c_str(), passwd.c_str());
#else

#endif
  // 执行sql语句
  ret = sqlite3_exec(myDB, requestSql, NULL, NULL, NULL);
  if (ret != SQLITE_OK)
  {
    cout << "sqlite3 open error2" << sqlite3_errmsg(myDB) << endl;
    _exit(-1);
  }

  cout << "指定用户名";
  cin >> username;

  string changepasswd;
  cout << "更改用户密码";
  cin >> changepasswd;

  char buffer2[64] = "update userInfo set passwd = %s where username = '%s';";
  char requestSql2[128] = {0};
  sprintf(requestSql2, buffer2, changepasswd.c_str(), username.c_str());

  // 执行sql语句
  ret = sqlite3_exec(myDB, requestSql2, NULL, NULL, NULL);
  if (ret != SQLITE_OK)
  {
    cout << "sqlite3 open error" << sqlite3_errmsg(myDB) << endl;
    _exit(-1);
  }
}

int main()
{
  sqlite3 *myDB = NULL;
  const char *baseName = "./test2.db";

  // 连接数据库

  int ret = sqlite3_open(baseName, &myDB);
  if (ret != SQLITE_OK)
  {
    cout << "sqlite3 open error" << sqlite3_errmsg(myDB) << endl;
    _exit(-1);
  }


  const char *sql = "SELECT * from userInfo;";

  //二级指针
  char **result = NULL;
  int Row = 0;
  int Column = 0;
  ret = sqlite3_get_table(myDB, sql, &result, &Row, &Column, NULL);
  if (ret != SQLITE_OK)
  {
    cout << "sqlite3_get_table error" << sqlite3_errmsg(myDB) << endl;
    _exit(-1);
  }
  cout << "row:" << Row << "  col:" << Column << endl;

  vector<vector<string>> Datas;
  for (int row = 1; row <= Row; row++)
  {
    vector<string> rowData;
    for (int col = 0; col < Column; col++)
    {
      // cout << left << setw(16) << result[row * Column + col];
      rowData.push_back(result[row * Column + col]);
    }
    Datas.push_back(rowData);
  }


  cout << "Datas.size:" << Datas.size() << endl;
  for (int idx = 0; idx <= Datas.size(); idx++)
  {
    vector<string> rowData = Datas[idx];
    for (int jdx = 0; jdx <= Datas.size(); jdx++)
    {
      cout << "rowData[" << jdx << "]= " << rowData[jdx] << "\t";
    }
    cout << endl;
  }

  // 关闭数据库
  sqlite3_close(myDB);
  return 0;
}
