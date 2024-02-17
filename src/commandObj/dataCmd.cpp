#include "dataCmd.h"

CDataCmd::CDataCmd(){}

CDataCmd::CDataCmd(std::vector<CDataBase*> dataBasePtrVec)
    :_dataBasePtrVec(dataBasePtrVec){}

//获取存储的数据数组
std::vector<CDataBase*> CDataCmd::get_data_vector_value() 
{
    return _dataBasePtrVec;
}

void CDataCmd::data_clean()
{
    _dataBasePtrVec.clear();
}

CDataCmd::~CDataCmd()
{
    _dataBasePtrVec.clear();
}
void CDataCmd::add_data_info(CDataBase* dataInfo)
{
    _dataBasePtrVec.push_back(dataInfo);
}