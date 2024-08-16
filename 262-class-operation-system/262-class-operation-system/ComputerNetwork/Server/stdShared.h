#ifndef __STDSHARED_H__
#define __STDSHARED_H__


enum FUNCTION_OPTION
{
    REGISTER = 1,   /* 注册 */
    LOGIN,          /* 登陆 */
    EXIT,
    ADDFRIEND,      /* 添加好友 */
    DELFRIEND,      /* 删除好友 */
    FRIENDCHAT,     /* 好友聊天 */
    FRIENDLIST,     /* 好友列表 */
    NEWGROUP,       /* 建群 */
    EXITGROUP,      /* 退群 */
    JOINGROUP,      /* 加入群聊 */
    INVITEGROUP,    /* 邀请群聊 */
    CHATGROUP,      /* 群聊聊天 */

    MATCH,          /* 匹配 */
    MOVE,           /* 移动 */
};

enum REPLY_CODE
{
    REGISTER_SUCCESS,       /* 注册成功 */
    REGISTER_USEREXIST,     /* 重复注册 */

    LOGIN_SUCCESS,          /* 登录成功. */
    LOGIN_PASSWD_ERROR,     /* 登录密码错误. */
    LOGIN_NOUSER,           /* 没有该用户. */
};

struct Msg
{
    FUNCTION_OPTION type; // 操作类型
    char name[20];
    char passwd[20];
    char toName[20];        // 目的好友


};



struct ReplyMsg
{
    FUNCTION_OPTION type;       // 操作类型
    REPLY_CODE statue_code;     // 回复的状态码
};




#endif // __STDSHARED_H__