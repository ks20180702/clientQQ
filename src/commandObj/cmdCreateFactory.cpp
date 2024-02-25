#include "cmdCreateFactory.h"
#include "loginCmd.h"
#include "friendshipChangeCmd.h"
#include "userChangeCmd.h"

CmdBase* CmdCreateFactory::create_cmd_ptr(CmdBase::CmdType inputCmdType)
{
    switch (inputCmdType)
    {
    case(CmdBase::LOGIN_CMD):
        return new CLoginCmd(); 
    
    default:
        return nullptr;
    }
}