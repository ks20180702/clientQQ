#include "./include/loginCmd.h"

CLoginCmd::CLoginCmd()
    :_loginUser(){_childCmdType=LOGIN_CMD;}
    
CLoginCmd::CLoginCmd(CUser &loginUser)
{
    _loginUser=loginUser;
    _childCmdType=LOGIN_CMD;
}  
int CLoginCmd::do_command()
{
    // _childDoCommandReturn=false; //开始时，执行成功标记设置为false

    // int existRe,friendNumRe,notRevcMsgNumRe;

    // // 1.检查用户账号密码，
    // existRe=cmdOtlUse.select_user_exist(_loginUser);
    // if(existRe!=0) {std::cout<<cmdOtlUse.get_errmsg()<<std::endl;return -1;}

    // // 使用户的id与account保持一致(测试时自己手动创建用户，可能会不一致)，正式不会这样
    // if(cmdOtlUse.set_user_id_by_account(_loginUser)==-1) 
    // {std::cout<<cmdOtlUse.get_errmsg()<<std::endl;return -1;}

    // // 2.获取该用户的好友数据
    // friendNumRe=cmdOtlUse.get_user_friends(_loginUser.get_id(),_friendLists);
    // if(friendNumRe==-1) {std::cout<<cmdOtlUse.get_errmsg()<<std::endl;return -1;}
    // std::cout<<"[I]  user have friend num = "<<friendNumRe<<std::endl;

    // // 3.获取消息未接收情况
    // notRevcMsgNumRe=cmdOtlUse.get_not_recv_msg(_loginUser.get_id(),_notRecvMsgsLists);
    // if(notRevcMsgNumRe==-1) {std::cout<<cmdOtlUse.get_errmsg()<<std::endl;return -1;}
    // std::cout<<"[I]  user have no recv msg num = "<<notRevcMsgNumRe<<std::endl;
    
    // // 4.发送用户成功消息+好友信息+为接收的信息数量(不加内容)
    // _childDoCommandReturn=true;
    return 0;
}

std::string CLoginCmd::get_command_obj_json()
{
    std::ostringstream ss;
    cereal::JSONOutputArchive archiveOut(ss);
    archiveOut(cereal::make_nvp("logInfo._childCmdType", this->_childCmdType),cereal::make_nvp("logInfo", *this));

    return ss.str();
}

void CLoginCmd::set_login_user(CUser &loginUser)
{
    _loginUser=loginUser;
}
CUser CLoginCmd::get_login_user()
{
    return _loginUser;
}

std::vector<CUser> &CLoginCmd::get_friend_lists()
{
    return _friendLists;
}
std::vector<CMsg> &CLoginCmd::get_not_recv_msg_lists()
{
    return _notRecvMsgsLists;
}
void CLoginCmd::set_friend_lists(std::vector<CUser> &friendLists)
{
    _friendLists=friendLists;
}

void CLoginCmd::set_not_recv_msg_lists(std::vector<CMsg> &notRecvMsgsLists)
{
    _notRecvMsgsLists=notRecvMsgsLists;
}

CLoginCmd::~CLoginCmd(){
    _friendLists.clear();
    _notRecvMsgsLists.clear();
}

