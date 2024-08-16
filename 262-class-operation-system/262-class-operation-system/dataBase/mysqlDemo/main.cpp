#include <iostream>
using namespace std;
#include <mysql/mysql.h>
#include <stdlib.h>
#include <iomanip>
#include "mysqlDataBase.h"

int main()
{
    stdMysqlDatabase mysqlDB;
    if (mysqlDB.connectDB("demoTest") == false)
    {
        cout <<"连接失败" <<endl;
        exit(-1);
    }
cout << "连接成功"<<endl;
//     std::string sql = "insert into students (name, age, grade) values ('zhou',23,'F');";
// mysqlDB.execute(sql);

    std::string sql = "SELECT grade, COUNT(id) FROM students WHERE age > 23 GROUP BY grade;";
mysqlDB.execute(sql);
mysqlDB.query(sql);

mysqlDB.closeDB();

    return 0;
}