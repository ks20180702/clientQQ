#include "./include/heartRequestCmd.h"

CHeartRequestCmd::CHeartRequestCmd()
    :_currentUser(){_childCmdType=HEART_CMD;}

CHeartRequestCmd::CHeartRequestCmd(CUser &currentUser)
{
    _currentUser=currentUser;
    _childCmdType=HEART_CMD;
}

#ifdef SERVER_PROGRAM
    CmdBase::DoCommandReturnType CHeartRequestCmd::do_command(COtlUse &cmdOtlUse,std::string &account)
    {
        _childDoCommandReturn=false; //开始时，执行成功标记设置为false

        int existRe,friendNumRe,requestUserRe;

        _currentUser.print();

        // 1.检查用户账号密码，暂时还是检查一下吧，
        existRe=cmdOtlUse.select_user_exist(_currentUser);
        if(existRe!=0) {std::cout<<cmdOtlUse.get_errmsg()<<std::endl;return ERROR_CMD;}
        // 使用户的id与account保持一致(测试时自己手动创建用户，可能会不一致)，正式不会这样
        if(cmdOtlUse.set_user_id_by_account(_currentUser)==-1) 
        {std::cout<<cmdOtlUse.get_errmsg()<<std::endl;return ERROR_CMD;}

        // 2.获取该用户的好友数据
        friendNumRe=cmdOtlUse.get_user_friends(_currentUser.get_id(),_friendLists);
        if(friendNumRe==-1) {std::cout<<cmdOtlUse.get_errmsg()<<std::endl;return ERROR_CMD;}
        std::cout<<"[I]  user have friend num = "<<friendNumRe<<std::endl;

        // 3.获取好友申请列表
        requestUserRe=cmdOtlUse.get_request_users(_currentUser.get_id(),_requestUserLists);
        if(requestUserRe==-1) {std::cout<<cmdOtlUse.get_errmsg()<<std::endl;return ERROR_CMD;}
        std::cout<<"[I]  user have request friend num = "<<requestUserRe<<std::endl;
        
        _childDoCommandReturn=true;
        return NORMAL_CMD;
    }
#endif

//获取当前指令对象的json字符串
std::string CHeartRequestCmd::get_command_obj_json()
{
    std::ostringstream ostrStream;
    cereal::JSONOutputArchive jsonOA(ostrStream);
    super_json_add_make_nvp(jsonOA,this->_childCmdType);
    
    jsonOA(cereal::make_nvp("heartInfo", *this));

    return ostrStream.str();
}

//重新加载接收到的对象(服务器存储有用数据的对象)
void CHeartRequestCmd::reload_recv_obj_by_json(cereal::JSONInputArchive &jsonIA)
{
    jsonIA(cereal::make_nvp("heartInfo", *this));
}

void CHeartRequestCmd::show_do_command_info()
{
    if(!_childDoCommandReturn)
    {
        std::cout<<"[E]  账号密码错误，退出"<<std::endl;
        return ;
    }
    std::cout<<"[I]  心跳请求"<<std::endl;
    std::vector<CUser> friendLists=get_friend_lists();
    std::vector<CUser> requestUserLists=get_friendship_request_lists();
    for(std::vector<CUser>::iterator it=friendLists.begin();it!=friendLists.end();it++)
    {
        (*it).print();
    }
    for(std::vector<CUser>::iterator it=requestUserLists.begin();it!=requestUserLists.end();it++)
    {
        (*it).print();
    }
}

// 设置当前的已登录对象
void CHeartRequestCmd::set_login_user(CUser &currentUser)
{
    _currentUser=currentUser;
}

//返回好友列表的引用
std::vector<CUser> &CHeartRequestCmd::get_friend_lists()
{
    return _friendLists;
}

//返回好友申请列表
std::vector<CUser> &CHeartRequestCmd::get_friendship_request_lists()
{
    return _requestUserLists;
}

//设置好友列表
void CHeartRequestCmd::set_friend_lists(std::vector<CUser> &friendLists)
{
    _friendLists=friendLists;
}

//设置未接收消息
void CHeartRequestCmd::set_friendship_request_lists(std::vector<CUser> &requestUserLists)
{
    _requestUserLists=requestUserLists;
}



CHeartRequestCmd::~CHeartRequestCmd()
{
    _friendLists.clear();
    _requestUserLists.clear();
}
