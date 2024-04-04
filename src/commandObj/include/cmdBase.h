#ifndef __CMDBASE_H__
#define __CMDBASE_H__

/*
    执行指令的基类，只可使用基指针，不允许创建
*/

// 【未实现】
// 暂时的几个指令的 get_next_command 和get_send_command都没实现
#include <memory>
#include "k_total_head.h"
#include "otlUse.h"


#define SERVER_PROGRAM //后面删掉，在其他的里面包含了，这里加一下，是让后面的好看一点

class CmdBase
{
public:
    enum CmdType
    {
        LOGIN_CMD,
        DTAT_MSG_CMD,
        USER_CHANGE_CMD,
        FRIEND_SHIP_CHANGE_CMD,
        HEART_CMD,
    };
    enum DoCommandReturnType
    {
        NORMAL_CMD, //正常执行的指令，将处理后的指令转发回客户端
        ERROR_CMD, //正常执行失败的指令，转发回客户端
        NEW_LOGIN_CMD, //新登录对象的指令，将处理后的指令转发回客户端，并记录该用户的sockAddr_in对象
        RE_TREANSMISSION_CMD, //转发指令，需要先由账号查到到对应的sockAddr_in，再发送过去
        NO_SEND_CMD, //不需要发送回客户端，直接跳过
    };
public:
    CmdBase(){_childDoCommandReturn=false;};

    virtual ~CmdBase(){};

#ifdef SERVER_PROGRAM
    //执行当前指令
    virtual CmdBase::DoCommandReturnType do_command(COtlUse &cmdOtlUse,std::string &account)=0;
#endif
    //获取当前指令对象的json字符串
    virtual std::string get_command_obj_json()=0;

    //重新加载接收到的对象(服务器存储有用数据的对象)
    virtual void reload_recv_obj_by_json(cereal::JSONInputArchive &jsonIA)=0;

    //显示返回信息(用于查看服务器端执行情况)
    virtual void show_do_command_info()=0;


    //重新加载接收到的对象(服务器存储有用数据的对象)
    virtual void reload_recv_obj_by_str(std::string cmdStr)
    {    
        std::istringstream istrStream(cmdStr+CMD_STR_ADD);
        cereal::JSONInputArchive jsonIA(istrStream);
        this->reload_recv_obj_by_json(jsonIA);
    };

    //由于序列化时必须加入子类子类类型，所以放到父类中
    void super_json_add_make_nvp(cereal::JSONOutputArchive &jsonOA,CmdBase::CmdType inputCmdType ){
        jsonOA(cereal::make_nvp("_childCmdType", inputCmdType));
    };

public:
    CmdType _childCmdType;

    bool _childDoCommandReturn; //执行do_command的结果，成功true，失败false
};


#endif