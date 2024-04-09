#ifndef __HREATMSGCMD_H__
#define __HREATMSGCMD_H__

/*
    由于端口问题(无法实时转发消息)，只能通过心跳请求的方式获取未读消息。
    与心跳请求执行逻辑一致(心跳请求每隔30秒发送一次，这样的话消息延迟
        太久了，所以单独弄个类，暂定5秒请求一次)
    可以放到heartRequestCmd类中，但是不好。
*/
#include "cmdBase.h"
#include "user.h"
#include "msg.h"

#include <sstream>
#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>

#include <map>
#include <vector>

class CHeartMsgCmd:public CmdBase
{

public:
    CHeartMsgCmd();
    CHeartMsgCmd(CUser &currentUser);
    ~CHeartMsgCmd();

#ifdef SERVER_PROGRAM
    // 收到该指令时，执行预设功能，获取当前用户未读消息
    virtual CmdBase::DoCommandReturnType do_command(COtlUse &cmdOtlUse);
#endif
    
    //获取当前指令对象的json字符串
    virtual std::string get_command_obj_json();

    //重新加载接收到的对象(服务器存储有用数据的对象)
    virtual void reload_recv_obj_by_json(cereal::JSONInputArchive &jsonIA);

    virtual void show_do_command_info();

    // 设置当前的已登录对象
    void set_current_user(CUser &currentUser);

    // 获取登录对象的值(非同一个)，用于查看
    CUser get_current_user();

    //返回未接收消息的引用
    std::vector<CMsg> &get_not_recv_msg_lists();

    //设置未接收消息
    void set_not_recv_msg_lists(std::vector<CMsg> &notRecvMsgsLists);

    //返回不同用户未接受消息的map
    std::map<int,std::vector<CMsg>> get_msg_part_account_map();

    //序列化
    template <class Archive>
    void serialize(Archive & ar)
	{
		ar(cereal::make_nvp("_childDoCommandReturn", _childDoCommandReturn),
        cereal::make_nvp("_currentUser", _currentUser), 
        cereal::make_nvp("_notRecvMsgsLists", _notRecvMsgsLists));
	}

private:
    //当前已登录的对象
    CUser _currentUser;

    //用户未接收的信息
    std::vector<CMsg> _notRecvMsgsLists;
};

#endif