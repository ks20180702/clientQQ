#include "./include/msgData.h"

CMsgData::CMsgData()
    :_num(0){}
CMsgData::CMsgData(int num)
    :_num(num){};

CMsgData& CMsgData::operator=(const CMsgData &other)
{
    _num=other._num;
    return *this;
}
void CMsgData::print()
{
    std::cout<<"num = "<<_num<<std::endl;
}