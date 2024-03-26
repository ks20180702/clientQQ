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
public:
    CmdBase(){_childDoCommandReturn=false;};

    virtual ~CmdBase(){};

    //执行当前指令
    virtual int do_command(COtlUse &cmdOtlUse)=0;

    //获取当前指令对象的json字符串
    virtual std::string get_command_obj_json()=0;

    //重新加载接收到的对象(服务器存储有用数据的对象)
    virtual void reload_recv_obj_by_str(std::string cmdStr)
    {    
        std::istringstream istrStream(cmdStr+CMD_STR_ADD);
        cereal::JSONInputArchive jsonIA(istrStream);
        this->reload_recv_obj_by_json(jsonIA);
    };

    //重新加载接收到的对象(服务器存储有用数据的对象)
    virtual void reload_recv_obj_by_json(cereal::JSONInputArchive &jsonIA)=0;

    //显示返回信息(用于查看服务器端执行情况)
    virtual void show_do_command_info()=0;

    //由于序列化时必须加入子类子类类型，所以放到父类中
    void super_json_add_make_nvp(cereal::JSONOutputArchive &jsonOA,CmdBase::CmdType inputCmdType ){
        jsonOA(cereal::make_nvp("_childCmdType", inputCmdType));
    };

public:
    CmdType _childCmdType;

    bool _childDoCommandReturn; //执行do_command的结果，成功true，失败false
};


#endif