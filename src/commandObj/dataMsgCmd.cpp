#include "dataMsgCmd.h"

CDataMsgCmd::CDataMsgCmd(CMsgData msgData)
{
    _msgData=msgData;
}

CDataBase* CDataMsgCmd::get_data_value()
{
    return (CDataBase*)(&_msgData);
}