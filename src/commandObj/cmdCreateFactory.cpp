#include "cmdCreateFactory.h"
#include "loginCmd.h"
#include "dataMsgCmd.h"
#include "friendshipChangeCmd.h"
#include "userChangeCmd.h"
#include "heartRequestCmd.h"
#include "heartMsgCmd.h"

CmdBase* CmdCreateFactory::create_cmd_ptr(CmdBase::CmdType inputCmdType)
{
    switch (inputCmdType)
    {
    case(CmdBase::LOGIN_CMD):
        return new CLoginCmd(); 
    case(CmdBase::DTAT_MSG_CMD):
        return new CDataMsgCmd(); 
    case(CmdBase::USER_CHANGE_CMD):
        return new CUserChangeCmd(); 
    case(CmdBase::FRIEND_SHIP_CHANGE_CMD):
        return new CFriendshipChangeCmd(); 
    case(CmdBase::HEART_CMD):
        return new CHeartRequestCmd(); 
    case(CmdBase::HEART_MSG_CMD):
        return new CHeartMsgCmd(); 
    default:
        return nullptr;
    }
}