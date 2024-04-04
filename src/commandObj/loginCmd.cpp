#include "./include/loginCmd.h"

CLoginCmd::CLoginCmd()
    :_loginUser(){_childCmdType=LOGIN_CMD;}
    
CLoginCmd::CLoginCmd(CUser &loginUser)
{
    _loginUser=loginUser;
    _childCmdType=LOGIN_CMD;
} 

#ifdef SERVER_PROGRAM
    CmdBase::DoCommandReturnType CLoginCmd::do_command(COtlUse &cmdOtlUse,std::string &account)
    {
        _childDoCommandReturn=false; //开始时，执行成功标记设置为false

        int existRe,friendNumRe,notRevcMsgNumRe;

        _loginUser.print();

        // 1.检查用户账号密码，
        existRe=cmdOtlUse.select_user_exist(_loginUser);
        if(existRe!=0) {std::cout<<cmdOtlUse.get_errmsg()<<std::endl;return ERROR_CMD;}

        // 使用户的id与account保持一致(测试时自己手动创建用户，可能会不一致)，正式不会这样
        if(cmdOtlUse.set_user_id_by_account(_loginUser)==-1) 
        {std::cout<<cmdOtlUse.get_errmsg()<<std::endl;return ERROR_CMD;}

        // 2.获取该用户的好友数据
        friendNumRe=cmdOtlUse.get_user_friends(_loginUser.get_id(),_friendLists);
        if(friendNumRe==-1) {std::cout<<cmdOtlUse.get_errmsg()<<std::endl;return ERROR_CMD;}
        std::cout<<"[I]  user have friend num = "<<friendNumRe<<std::endl;

        // 3.获取消息未接收情况
        notRevcMsgNumRe=cmdOtlUse.get_not_recv_msg(_loginUser.get_id(),_notRecvMsgsLists);
        if(notRevcMsgNumRe==-1) {std::cout<<cmdOtlUse.get_errmsg()<<std::endl;return ERROR_CMD;}
        std::cout<<"[I]  user have no recv msg num = "<<notRevcMsgNumRe<<std::endl;
        
        //获取当前用户的账号
        account=_loginUser.get_account();
        _childDoCommandReturn=true;
        return NEW_LOGIN_CMD;
    }
#endif

std::string CLoginCmd::get_command_obj_json()
{
    std::ostringstream ostrStream;
    cereal::JSONOutputArchive jsonOA(ostrStream);
    super_json_add_make_nvp(jsonOA,this->_childCmdType);
    
    jsonOA(cereal::make_nvp("logInfo", *this));

    return ostrStream.str();
}

void CLoginCmd::reload_recv_obj_by_json(cereal::JSONInputArchive &jsonIA) 
{
    jsonIA(cereal::make_nvp("logInfo", *this));
}

void CLoginCmd::show_do_command_info()
{
    if(!_childDoCommandReturn)
    {
        std::cout<<"[E]  账号密码错误，请重新输入"<<std::endl;
        return ;
    }
    std::cout<<"[I]  欢迎登录"<<std::endl;
    std::vector<CUser> friendLists=get_friend_lists();
    std::vector<CMsg> notRecvMsgsLists=get_not_recv_msg_lists();
    for(std::vector<CUser>::iterator it=friendLists.begin();it!=friendLists.end();it++)
    {
        (*it).print();
    }
    for(std::vector<CMsg>::iterator it=notRecvMsgsLists.begin();it!=notRecvMsgsLists.end();it++)
    {
        (*it).print();
    }
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

