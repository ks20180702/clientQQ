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

    virtual void reload_recv_obj(std::string cmdStr){};

        //显示返回信息
    virtual void show_do_command_info(){};

private:
    CMsgData _msgData;
};

#endif