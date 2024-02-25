#ifndef __FRIENDSHIPCHANGECMD_H__
#define __FRIENDSHIPCHANGECMD_H__

#include "cmdBase.h"
#include "user.h"
#include "msg.h"


/*
    实现好友关系修改命令
    1.删除好友关系
    2.添加好友关系
*/

class CFriendshipChangeCmd:public CmdBase
{
public:
    enum OperatorFriendShipType
    {
        DELETT_FRIEND, //删除好友关系
        ADD_FRIEND,//客户端的好友申请
        ADD_FRIEND_TO_CLIENT, //增加好友关系申请指令(发送给客户端)
        ADD_FRIEND_TO_SERVER //好友同意(发送给服务器端)
    };
public:
    CFriendshipChangeCmd();
    CFriendshipChangeCmd(CUser &myUser,CUser &friendUser,OperatorFriendShipType friendType);
    ~CFriendshipChangeCmd() override;

    // 执行好友关系处理相关命令
    // 错误-1，0增加成功/修改成功
    virtual int do_command(COtlUse &cmdOtlUse);

    virtual std::string get_command_obj_json();

    //重新加载接收到的对象(服务器存储有用数据的对象)
    virtual void reload_recv_obj_by_json(cereal::JSONInputArchive &jsonIA);

    virtual void show_do_command_info();
     
    //设置需操作的用户，用户的好友，操作类型
    void set_user(CUser &myUser);
    void set_friend_user(CUser &friendUser);
    void set_operator_type(OperatorFriendShipType friendType);

    //序列化
    template <class Archive>
    void serialize(Archive & ar)
	{
		ar(cereal::make_nvp("_childDoCommandReturn", _childDoCommandReturn),
        cereal::make_nvp("_myUser", _myUser),
        cereal::make_nvp("_friendUser", _friendUser), 
        cereal::make_nvp("_friendType", _friendType));
	}

private:
    //当前需要操作的对象
    CUser _myUser,_friendUser;

    OperatorFriendShipType _friendType;
};

#endif