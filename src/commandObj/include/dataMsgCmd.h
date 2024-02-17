#ifndef __DATAMSGCMD_H__
#define __DATAMSGCMD_H__

#include "dataCmdBase.h"
#include "msgData.h"
/*
    传输发送的消息的指令
*/
class CDataMsgCmd:public CDataCmdBase
{
public:
    CDataMsgCmd(){};
    CDataMsgCmd(CMsgData msgData);

    virtual ~CDataMsgCmd() override{};

    virtual CDataBase* get_data_value() override;

private:
    CMsgData _msgData;
};

#endif