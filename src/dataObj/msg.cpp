#include "./include/msg.h"

CMsg::CMsg()
    :_sendId(0),_recvId(0),_msgDateTime(""),_content("")
{}

CMsg::CMsg(const CMsg &other)
{
    *this = other;
}
CMsg::CMsg(int sendId,int recvId,char *msgDateTime,char* content)
{
    this->set_msg_info(sendId,recvId,msgDateTime,content);
}


//为用户设置对应的值
void CMsg::set_msg_info(int sendId,int recvId,char *msgDateTime,char* content)
{
    //此处需加一个长度检查
    //暂时赋值会产生地址越界的可能错误
    
    _sendId=sendId;
    _recvId=recvId;
    _msgDateTime=std::string(msgDateTime);
    _content=std::string(content);
}
// 用发送id和接收id来判断是否相等
bool CMsg::operator==(const CMsg &other)
{
    if(_sendId==other.get_send_id()&&_recvId==other.get_recv_id())
    {
        return true;
    }
    else return false;
}
CMsg &CMsg::operator=(const CMsg &other)
{
    this->set_msg_info(other.get_send_id(),other.get_recv_id(),
                        other.get_msg_dt(),other.get_content());
    return *this;
}

// 返回对应的变量值
int CMsg::get_send_id() const
{
    return _sendId;
}
int CMsg::get_recv_id() const
{
    return _recvId;
}
char *CMsg::get_msg_dt() const
{
    return (char*)(_msgDateTime.c_str());
}
char *CMsg::get_content() const
{
    return (char*)(_content.c_str());
}
void CMsg::print()
{
    std::cout<<"send id = "<<this->get_send_id();
    std::cout<<"; recv id = "<<this->get_recv_id();
    std::cout<<"; msg datetime  = "<<this->get_msg_dt();
    std::cout<<"; content = "<<this->get_content()<<std::endl;
}


CMsg::~CMsg()
{
    
}