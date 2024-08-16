#ifndef __CHATROOM_H__
#define __CHATROOM_H__

#include "stdTcpServer.h"


class ChatRoom
{
public:
    /* 构造函数 */
    ChatRoom(const StdTcpSocketPtr & clientInfo);

    /* 析构函数 */
    ~ChatRoom();
public:
    /* 聊天室入口 */
    void ChatEnter();

private:
    /* 聊天菜单 */
    void ChatMenu();

    /* 添加好友 */
    void addFriend();

    /* 删除好友 */
    void delFriend();

    
private:
    StdTcpSocketPtr m_clientSock;

    /* 偏移 */
    static const int m_offset = 3;
};


#endif //__CHATROOM_H__