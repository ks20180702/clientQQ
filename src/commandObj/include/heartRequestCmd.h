#ifndef __HEARTREQUEST_H__
#define __HEARTREQUEST_H__

/*
    实现心跳指令(类似登录指定)
     由用户端发起，暂定5秒一次，用于确定用户是否在线。
     服务器端返回一些不需实时更新的信息(如新增加的好友关系，好友申请)，实时消息不放在这里
*/
#include "cmdBase.h"
#include "user.h"
#include "msg.h"

#include <sstream>
#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>

class CHeartRequestCmd:public CmdBase
{

public:
    CHeartRequestCmd();
    CHeartRequestCmd(CUser &currentUser);
    ~CHeartRequestCmd();

#ifdef SERVER_PROGRAM
    // 收到该指令时，执行预设功能
    //  1.获取该用户的好友数据，2.获取好友申请
    // 错误-1，成功0
    virtual CmdBase::DoCommandReturnType do_command(COtlUse &cmdOtlUse,std::string &account);
#endif
    
    //获取当前指令对象的json字符串
    virtual std::string get_command_obj_json();

    //重新加载接收到的对象(服务器存储有用数据的对象)
    virtual void reload_recv_obj_by_json(cereal::JSONInputArchive &jsonIA);

    virtual void show_do_command_info();

    // 设置当前的已登录对象
    void set_login_user(CUser &loginUser);

    // 获取登录对象的值(非同一个)，用于查看
    CUser get_login_user();

    //返回好友列表的引用
    std::vector<CUser> &get_friend_lists();

    //返回好友申请列表
    std::vector<CUser> &get_friendship_request_lists();

    //设置好友列表
    void set_friend_lists(std::vector<CUser> &friendLists);

    //设置未接收消息
    void set_friendship_request_lists(std::vector<CUser> &requestUserLists);



    //序列化
    template <class Archive>
    void serialize(Archive & ar)
	{
		ar(cereal::make_nvp("_childDoCommandReturn", _childDoCommandReturn),
        cereal::make_nvp("_currentUser", _currentUser),
        cereal::make_nvp("_friendLists", _friendLists), 
        cereal::make_nvp("_requestUserLists", _requestUserLists));
	}

private:
    //当前已登录的对象
    CUser _currentUser;

//可以考虑不作为成员变量
    //当前用户的好友信息
    std::vector<CUser> _friendLists;

    //用户为接收的信息
    std::vector<CUser> _requestUserLists;
};

#endif