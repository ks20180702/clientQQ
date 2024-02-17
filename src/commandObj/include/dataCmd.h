#ifndef __DATACCMDBASE_H__
#define __DATACCMDBASE_H__

#include "cmdBase.h"
#include "dataBase.h"
#include <vector>

/*
    数据指令，继承CNotOperatorCmd，作为携带数据的指令
*/
class CDataCmd:public CmdBase
{
public:
    CDataCmd();
    CDataCmd(std::vector<CDataBase*> dataBasePtrVec);

    ~CDataCmd();
    //获取存储的数据数组
    std::vector<CDataBase*> get_data_vector_value();
    
    //清空vector
    void data_clean();

    //加入一个数据指针到vector中
    void add_data_info(CDataBase* dataInfo);

private:
    std::vector<CDataBase*> _dataBasePtrVec;
};

#endif