#include "function.h"
#include <cstring>
#include "stdDataBase.h"
#include "sqliteDataBase.h"

/* 构造函数 */
Function::Function(const StdTcpSocketPtr & clientInfo)
{
    m_clientInfo = clientInfo;

    m_sqliteDB.connectDB("./test2.db");
}

/* 析构函数 */
Function::~Function()
{

}

void Function::handleRegisterInfo(const Msg & msg)
{
    /* todo... */
    std::cout << "username:" << msg.name << std::endl;
    std::cout << "passwd:" << msg.passwd << std::endl;

   // string replyInfo = "注册成功.";
    //m_clientInfo->sendMessage(replyInfo);
    ReplyMsg responseMsg;
    responseMsg.type = REGISTER;
    //判断用户是否存在
    if(userIsExist(msg.name)== true)
    {
        responseMsg.statue_code = REGISTER_USEREXIST;
    }
    else
    {
        responseMsg.statue_code = REGISTER_SUCCESS;
    }
    //将信息发送回客户端
   this->m_clientInfo->sendMessage(static_cast<const void *> (&responseMsg), sizeof(responseMsg));
}
//登陆函数
void Function::handleLoginInfo(const Msg & msg)
{
    std::cout << "username:" << msg.name << std::endl;
    std::cout << "passwd:" << msg.passwd << std::endl;

   // string replyInfo = "登陆失败, 密码不正确.";
  //  m_clientInfo->sendMessage(replyInfo);

string username(msg.name);
string passwd(msg.passwd);

ReplyMsg respenseMsg;

memset(&respenseMsg, 0 , sizeof(respenseMsg));
respenseMsg.type = LOGIN;
    if (username == "zhangsan")
    {
        if(passwd == "123")
        {
            //用户名与密码匹配
            respenseMsg.statue_code=LOGIN_SUCCESS;
        }
        else
        {
            //用户名与密码不匹配
        respenseMsg.statue_code = LOGIN_PASSWD_ERROR;
        }
    }else{
        //没有该用户
        respenseMsg.statue_code = LOGIN_NOUSER;
    }
//送回客户端
    m_clientInfo->sendMessage(static_cast<const void *>(&respenseMsg), sizeof(respenseMsg));
#if 0
    /* 判断用户名是否已经注册 */
    if (userIsExist(username) == false)
    {
        /* 程序进入这个里面, 说明用户名不存在 */


        /* 将信息发送到客户端 */
        
    }
    else 
    {
        /* 如果用户名存在, 判断用户名和密码是否匹配 */
        userIsMatchPasswd(username, passwd);

        /* 判断用户是否已经登陆 */
        userIsOnlined(username);
    }
#endif

}


/* 判断用户名是否存在 */
bool Function::userIsExist(const char * username)
{
   // stdSqliteDataBase sdb;
  // sdb.connectDB("./text2.db");
   string sql = "select const(1) from userInfo where username = '%s';";
   char requestSql[128]= {0};
   sprintf(requestSql, sql.c_str(), username );

   std::vector<vector<string>> res = m_sqliteDB.query(requestSql);
   if (res[0][0] == "0")
   {
    return false;
   }
    return true;
}

/* 用户名和密码是否匹配 */
bool Function::userIsMatchPasswd(const char * username, const char *  passwd)
{
    /* todo... */
    return true;
}

/* 用户是否已经登陆/在线 */
bool Function::userIsOnlined(const char * username)
{
    /* todo... */
    return true;
}
void Function::handleAddFriendInfo(const Msg & msg)
{
    cout << "msg.toName" << msg.toName << endl;
}