#include "chatroom.h"
#include "stdShared.h"
#include <cstring>

/* 构造函数 */
ChatRoom::ChatRoom(const StdTcpSocketPtr & clientInfo): m_clientSock(clientInfo)
{

}

/* 析构函数 */
ChatRoom::~ChatRoom()
{

}


/* 聊天菜单 */
void ChatRoom::ChatMenu()
{
    std::cout << "1.添加好友" << std::endl;
    std::cout << "2.删除好友" << std::endl;
    std::cout << "3.好友聊天" << std::endl;
    std::cout << "4.好友列表" << std::endl;

    std::cout << "5.创建群聊" << std::endl;
    std::cout << "6.退出群聊" << std::endl;
    std::cout << "7.加入群聊" << std::endl;
    std::cout << "8.邀请进聊" << std::endl;
    std::cout << "9.群聊聊天" << std::endl;
}

/* 添加好友 */
void ChatRoom::addFriend()
{
    string addName;
    cout << "请输入添加联系人的用户名:" << endl;
    cin >> addName;

    Msg msg;
    memset(&msg, 0, sizeof(msg));

    msg.type = ADDFRIEND;
    strncpy(msg.toName, addName.c_str(), sizeof(msg.toName) - 1);
    
    /* 发送信息给服务器 */
    m_clientSock->sendMessage((const void *)&msg, sizeof(msg));
}

/* 删除好友 */
void ChatRoom::delFriend()
{
    string delName;
    cout << "请输入删除联系人的用户名:" << endl;
    cin >> delName;

    /* 发送信息给服务器 */
    m_clientSock->sendMessage(delName);
}

/* 聊天室入口 */
void ChatRoom::ChatEnter()
{
    ChatMenu();

    int choice = 0;
    cin >> choice;

    choice += m_offset;

    switch (choice)
    {
    case ADDFRIEND:
        addFriend();
        break;
    case DELFRIEND:
       delFriend();
        break;
    default:
        break;
    }
}
