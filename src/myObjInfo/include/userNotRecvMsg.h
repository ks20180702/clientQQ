#ifndef __USERNOTRECVMSG_H__
#define __USERNOTRECVMSG_H__
#include <k_total_head.h>

/*
    用户未读的好友消息数量类
*/

class CUserNotRecvMsg
{

public:
    CUserNotRecvMsg();
    CUserNotRecvMsg(int friendId,char* friendName,int msgNum);
    ~CUserNotRecvMsg();

    //设置变量值
    void set_info(int friendId,char* friendName,int msgNum);

    //获取变量值
    int get_friend_id() const;
    char *get_friend_name() const;
    int get_msg_num() const;
    void print();

private:
    //好友id
    int _friendId;

    //好友昵称
    char _friendName[32];

    //未读消息数量
    int _msgNum;  
};

#endif