#ifndef __USERNOTRECVMSG_H__
#define __USERNOTRECVMSG_H__
#include <k_total_head.h>
#include "dataBase.h"

#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>

/*
    用户未读的好友消息数量类
*/

class CUserNotRecvMsg:public CDataBase
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

    template <class Archive>
    void serialize(Archive & ar)
	{
		ar(cereal::make_nvp("_friendId", _friendId),
        cereal::make_nvp("_friendName", _friendName), 
        cereal::make_nvp("_msgNum",_msgNum));
	}

private:
    //好友id
    int _friendId;

    //好友昵称
    std::string _friendName;

    //未读消息数量
    int _msgNum;  
};

#endif