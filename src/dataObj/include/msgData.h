#ifndef __MSGDATA_H__
#define __MSGDATA_H__
#include "k_total_head.h"
#include "dataBase.h"
/*
    消息数据类，用于存储发送的消息信息
*/
class CMsgData:public CDataBase
{
public:
    CMsgData();
    CMsgData(int num);
    virtual ~CMsgData() override {};

    CMsgData& operator=(const CMsgData &other);

    void print();
private:
    int _num;
};


#endif