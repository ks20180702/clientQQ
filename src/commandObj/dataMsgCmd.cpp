#include "./include/dataMsgCmd.h"

CDataMsgCmd::CDataMsgCmd()
{
    _childCmdType=DTAT_MSG_CMD;
}
CDataMsgCmd::CDataMsgCmd(CUser &recvUser,CMsg &msgData) 
{
    _recvUser=recvUser;
    _msgData=msgData;
    _childCmdType=DTAT_MSG_CMD;
}

#ifdef SERVER_PROGRAM
    CmdBase::DoCommandReturnType CDataMsgCmd::do_command(COtlUse &cmdOtlUse)
    {
        _childDoCommandReturn=false; //开始时，执行成功标记设置为false

        int executeReturn;

        if(MSG_CONFIRM==_requestType)
        {
            executeReturn=cmdOtlUse.set_msg_read_over(_msgData.get_recv_id(),_msgData.get_send_id());
            if(executeReturn==-1) {std::cout<<cmdOtlUse.get_errmsg()<<std::endl;return ERROR_CMD;}
            std::cout<<"[MSG_CONFIRM]  is over"<<std::endl;
        }
        else if(MSG_SEND==_requestType)
        {
            //将接收到的消息入库
            executeReturn=cmdOtlUse.add_msg(_msgData);
            if(executeReturn==-1) {std::cout<<cmdOtlUse.get_errmsg()<<std::endl;return ERROR_CMD;}
            // account=_recvUser.get_account(); //接收对象的账号

            std::cout<<"[MSG_SEND]  is over"<<std::endl;
        }

        _childDoCommandReturn=true;
        return NORMAL_CMD;
    }
#endif

std::string CDataMsgCmd::get_command_obj_json()
{
    std::ostringstream ostrStream;
    cereal::JSONOutputArchive jsonOA(ostrStream);
    super_json_add_make_nvp(jsonOA,this->_childCmdType);
    
    jsonOA(cereal::make_nvp("dataMsg", *this));

    return ostrStream.str();
}
void CDataMsgCmd::reload_recv_obj_by_json(cereal::JSONInputArchive &jsonIA) 
{
    jsonIA(cereal::make_nvp("dataMsg", *this));
}

void CDataMsgCmd::show_do_command_info()
{
    std::cout<<"this user:"<<std::endl;
    _recvUser.print();
}


void CDataMsgCmd::set_msg_request_type(MsgRequestType requestType)
{
    _requestType=requestType;
}
void CDataMsgCmd::set_recv_user(CUser &recvUser)
{
    _recvUser=recvUser;
}
CUser CDataMsgCmd::get_recv_user()
{
    return _recvUser;
}
void CDataMsgCmd::set_msg_data(CMsg &msgData)
{
    _msgData=msgData;
}
CMsg& CDataMsgCmd::get_msg_data()
{
    return _msgData;
}

CDataMsgCmd::~CDataMsgCmd() {}
