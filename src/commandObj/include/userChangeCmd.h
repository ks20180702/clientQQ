#ifndef __USERCHANGECMD_H__
#define __USERCHANGECMD_H__

#include "cmdBase.h"
#include "user.h"
#include "msg.h"

#include <sstream>
#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>

/*
    实现用户修改命令
    1.用户信息修改
    2.添加用户
*/

class CUserChangeCmd:public CmdBase
{
public:
    enum OpratorType
    {
        CHANGE_USER, //修改用户
        ADD_USER //增加用户
    };
public:
    CUserChangeCmd();
    ~CUserChangeCmd() override;

#ifdef SERVER_PROGRAM
    // 执行用户处理相关命令
    // 错误-1，0增加成功/修改成功
    virtual CmdBase::DoCommandReturnType do_command(COtlUse &cmdOtlUse) override;
#endif
    
    //获取当前指令对象的json字符串
    virtual std::string get_command_obj_json() override;

    //重新加载接收到的对象(服务器存储有用数据的对象)
    virtual void reload_recv_obj_by_json(cereal::JSONInputArchive &jsonIA) ;

    virtual void show_do_command_info();
    
    //获取和设置用户(获取的并不是同一个)
    void set_operator_user(CUser &operatorUser);
    CUser get_operator_user();

    //设置该条指令的操作类型
    void set_operator_type(OpratorType operType);

    //序列化
    template <class Archive>
    void serialize(Archive & ar)
	{
		ar(cereal::make_nvp("_childDoCommandReturn", _childDoCommandReturn),
        cereal::make_nvp("_operatorUser", _operatorUser),
        cereal::make_nvp("_operType", _operType));
	}
private:
    //当前需要操作的对象
    CUser _operatorUser;

    OpratorType _operType;
};

#endif