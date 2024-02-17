#include "./include/userNotRecvMsg.h"


CUserNotRecvMsg::CUserNotRecvMsg()
    :_friendId(0),_friendName(""),_msgNum(0){}

CUserNotRecvMsg::CUserNotRecvMsg(int friendId,char* userName,int msgNum)
{
    set_info(friendId,userName,msgNum);
}

void CUserNotRecvMsg::set_info(int friendId,char* friendName,int msgNum)
{
    _friendId=friendId;
    _friendName=std::string(friendName);
    _msgNum=msgNum;
}

int CUserNotRecvMsg::get_friend_id() const
{
    return _friendId;
}
char *CUserNotRecvMsg::get_friend_name() const
{
    return (char *)(_friendName.c_str());
}
int CUserNotRecvMsg::get_msg_num() const
{
    return _msgNum;
}
void CUserNotRecvMsg::print()
{
    std::cout<<"friendId = "<<_friendId;
    std::cout<<" friendName = "<<_friendName;
    std::cout<<" msgNum = "<<_msgNum<<std::endl;
}
CUserNotRecvMsg::~CUserNotRecvMsg()
{
}