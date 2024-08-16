#ifndef __STD_DATABASE_H__
#define __STD_DATABASE_H__

#include <string>
#include <vector>
#include <iostream>
using namespace std;

using vecResult = std::vector<vector<string>>;

class stdDataBase
{
private:
    /* data */
public:

    virtual ~stdDataBase() = default;
public:
//is连接数据库
virtual bool connectDB(const std::string & dbFileName) =0;
//执行sql语句
virtual bool execute(const std::string sql) = 0;
//查询sql语句
virtual std::vector<vector<string>> query( const std::string sql) = 0;

virtual void closeDB() = 0;
    //注册（增加数据）
    //该密码（UPDATE）
    //
};

stdDataBase::stdDataBase(/* args */)
{
}

stdDataBase::~stdDataBase()
{
}




#endif // !__STD_DATABASE_H__
