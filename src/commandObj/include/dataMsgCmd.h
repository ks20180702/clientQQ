#ifndef __DATAMSGCMD_H__
#define __DATAMSGCMD_H__

/*
    传输发送的消息的指令
    by ks 2024-4-2
*/

#include "cmdBase.h"
#include "msg.h"
#include "user.h"


#include <sstream>
#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>

class CDataMsgCmd:public CmdBase
{
public:
    enum MsgRequestType
    {
        MSG_SEND, 
        MSG_CONFIRM, //消息确认，表示该好友间消息已查看
    };
public:
    CDataMsgCmd();
    CDataMsgCmd(CUser &userRecv,CMsg &msgData);
    ~CDataMsgCmd();

#ifdef SERVER_PROGRAM
    //执行当前指令
    virtual CmdBase::DoCommandReturnType do_command(COtlUse &cmdOtlUse);
#endif
    //获取当前指令对象的json字符串
    virtual std::string get_command_obj_json();

    //重新加载接收到的对象(服务器存储有用数据的对象)
    virtual void reload_recv_obj_by_json(cereal::JSONInputArchive &jsonIA);

    //显示返回信息(用于查看服务器端执行情况)
    virtual void show_do_command_info();


    // 设置和获取成员变量
    void set_msg_request_type(MsgRequestType requestType);
    void set_recv_user(CUser &recvUser);
    CUser get_recv_user();
    void set_msg_data(CMsg &_msgData);
    CMsg& get_msg_data();


    //序列化
    template <class Archive>
    void serialize(Archive & ar)
	{
		ar(cereal::make_nvp("_childDoCommandReturn", _childDoCommandReturn),
        cereal::make_nvp("_recvUser", _recvUser),
        cereal::make_nvp("_requestType", _requestType),
        cereal::make_nvp("_msgData", _msgData));
	}

private:
    CUser _recvUser; //接收消息的用户

    CMsg _msgData; //发送的消息

    MsgRequestType _requestType;
};

#endif