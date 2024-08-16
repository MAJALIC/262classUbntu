#include <iostream>
using namespace std;
#include "stdTcpServer.h"
#include <unistd.h>
#include "stdShared.h"
#include <cstring>
#include "chatroom.h"

/* 界面菜单 */
void interfaceMenu()
{
    cout << "1. 注册" << endl;
    cout << "2. 登陆" << endl;
    cout << "3. 退出" << endl;
}

/* 注册功能 */
void registerFunc(const StdTcpSocketPtr &client)
{
    string username;
    cout << "请输入用户名:";
    fflush(stdout);
    cin >> username;

    string passwd;
    cout << "请输入密码:";
    fflush(stdout);
    cin >> passwd;

    Msg msg;
    memset(&msg, 0, sizeof(msg));

    msg.type = REGISTER;
    strncpy(msg.name, username.c_str(), sizeof(msg.name) - 1);
    strncpy(msg.passwd, passwd.c_str(), sizeof(msg.passwd) - 1);

    /* 将用户名和密码发送给服务器 */
    client->sendMessage(&msg, sizeof(msg));


    ReplyMsg recvMsg;
    client->recvMessage((void *)&recvMsg, sizeof(recvMsg));

    if (recvMsg.statue_code == REGISTER_SUCCESS)
    {
        cout << "恭喜, 注册成功..." << endl;
    }
    else if (recvMsg.statue_code == REGISTER_USEREXIST)
    {
        cout << "重复注册, 用户已存在." << endl;
    }
}

/* 登陆功能 */
void loginFunc(const StdTcpSocketPtr &client)
{
    string username;
    cout << "请输入用户名:";
    fflush(stdout);
    cin >> username;

    string passwd;
    cout << "请输入密码:";
    fflush(stdout);
    cin >> passwd;

    Msg msg;
    memset(&msg, 0, sizeof(msg));

    msg.type = LOGIN;
    strncpy(msg.name, username.c_str(), sizeof(msg.name) - 1);
    strncpy(msg.passwd, passwd.c_str(), sizeof(msg.passwd) - 1);

    /* 将用户名和密码发送给服务器 */
    client->sendMessage(&msg, sizeof(msg));


    ReplyMsg recvMsg;
    client->recvMessage((void *)&recvMsg, sizeof(recvMsg));
    
    if (recvMsg.statue_code == LOGIN_SUCCESS)
    {
        cout << "登录成功" << endl;
        sleep(2);

        ChatRoom chatroom(client);
        chatroom.ChatEnter();
    }
    else if (recvMsg.statue_code == LOGIN_PASSWD_ERROR)
    {
        cout << "密码错误" << endl;
    }
    else if (recvMsg.statue_code == LOGIN_NOUSER)
    {
        cout << "没有该用户请先注册..." << endl;
    }
}


int main()
{
    /* 客户端 */
    StdTcpSocketPtr client = std::make_shared<StdTcpSocket>();

    /* 连接服务器 */
    const char * serverIp = "192.168.183.129";
    int ret = client->connectToServer(serverIp, 8080);
    if (ret != 0)
    {
        cout << "connectToServer failed." << endl;
        _exit(-1);
    }
    cout << "连接成功...\n";
    sleep(1);
    system("clear");

    int choice;
    while (1)
    {
        interfaceMenu();
        cout << "请输入你的选项:";
        cin >> choice;

        switch (choice)
        {
        case REGISTER:
            registerFunc(client);
            break;
        case LOGIN:
            loginFunc(client);
            break;
        case EXIT:
            exit(0);
            break;
        
        default:
            break;
        }
    }

    return 0;
}