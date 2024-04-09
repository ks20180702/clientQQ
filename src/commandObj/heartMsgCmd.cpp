#include "./include/heartMsgCmd.h"

CHeartMsgCmd::CHeartMsgCmd()
    :_currentUser(){_childCmdType=HEART_MSG_CMD;}
    
CHeartMsgCmd::CHeartMsgCmd(CUser &currentUser)
{
    _currentUser=currentUser;
    _childCmdType=HEART_MSG_CMD;
} 

#ifdef SERVER_PROGRAM
    CmdBase::DoCommandReturnType CHeartMsgCmd::do_command(COtlUse &cmdOtlUse)
    {
        _childDoCommandReturn=false; //开始时，执行成功标记设置为false

        int existRe,notRevcMsgNumRe;

        _currentUser.print();

        // 检查用户账号密码，
        existRe=cmdOtlUse.select_user_exist(_currentUser);
        if(existRe!=0) {std::cout<<cmdOtlUse.get_errmsg()<<std::endl;return ERROR_CMD;}

        // 使用户的id与account保持一致(测试时自己手动创建用户，可能会不一致)，正式不会这样
        if(cmdOtlUse.set_user_id_by_account(_currentUser)==-1) 
        {std::cout<<cmdOtlUse.get_errmsg()<<std::endl;return ERROR_CMD;}

        // 获取消息未接收情况
        notRevcMsgNumRe=cmdOtlUse.get_not_recv_msg(_currentUser.get_id(),_notRecvMsgsLists);
        if(notRevcMsgNumRe==-1) {std::cout<<cmdOtlUse.get_errmsg()<<std::endl;return ERROR_CMD;}
        std::cout<<"[I]  user have no recv msg num = "<<notRevcMsgNumRe<<std::endl;
        
        _childDoCommandReturn=true;
        return NORMAL_CMD;
    }
#endif

std::string CHeartMsgCmd::get_command_obj_json()
{
    std::ostringstream ostrStream;
    cereal::JSONOutputArchive jsonOA(ostrStream);
    super_json_add_make_nvp(jsonOA,this->_childCmdType);
    
    jsonOA(cereal::make_nvp("heartMsg", *this));

    return ostrStream.str();
}

void CHeartMsgCmd::reload_recv_obj_by_json(cereal::JSONInputArchive &jsonIA) 
{
    jsonIA(cereal::make_nvp("heartMsg", *this));
}

void CHeartMsgCmd::show_do_command_info()
{
    if(!_childDoCommandReturn)
    {
        std::cout<<"[E]  CHeartMsgCmd do command have a error "<<std::endl;
        return ;
    }
    //
    std::cout<<"[I] CHeartMsgCmd  show_do_command_info is succeed "<<std::endl;
}


void CHeartMsgCmd::set_current_user(CUser &currentUser)
{
    _currentUser=currentUser;
}
CUser CHeartMsgCmd::get_current_user()
{
    return _currentUser;
}

void CHeartMsgCmd::set_not_recv_msg_lists(std::vector<CMsg> &notRecvMsgsLists)
{
    _notRecvMsgsLists=notRecvMsgsLists;
}
std::vector<CMsg> &CHeartMsgCmd::get_not_recv_msg_lists()
{
    return _notRecvMsgsLists;
}
std::map<int,std::vector<CMsg>> CHeartMsgCmd::get_msg_part_account_map()
{
    std::map<int,std::vector<CMsg>> msgsPartAccountMap;
    std::map<int,std::vector<CMsg>>::iterator itMsgAccout;
    for(std::vector<CMsg>::iterator it=_notRecvMsgsLists.begin();it!=_notRecvMsgsLists.end();it++)
    {
        itMsgAccout=msgsPartAccountMap.find((*it).get_send_id());
        if(itMsgAccout==msgsPartAccountMap.end())
        {
            std::vector<CMsg> tempMsgVector;
            tempMsgVector.push_back((*it));
            msgsPartAccountMap.insert(std::map<int,std::vector<CMsg>>::value_type((*it).get_send_id(),tempMsgVector));
        }
        else{
            (itMsgAccout->second).push_back((*it));
        }
    }

    return msgsPartAccountMap;
}


CHeartMsgCmd::~CHeartMsgCmd(){
    _notRecvMsgsLists.clear();
}

