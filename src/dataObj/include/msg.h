#ifndef __MSG_H__
#define __MSG_H__
#include <k_total_head.h>

#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>

/*消息对象
    by ks 2023-11-26
    move to dataObj in 2023-12-4
*/
class CMsg
{

public:
    CMsg();
    CMsg(const CMsg &other);
    CMsg(int sendId,int recvId,char *msgDateTime,char* content);
    ~CMsg();

    //为用户设置对应的值
    void set_msg_info(int sendId,int recvId,char *msgDateTime,char* content);
    // 用发送id和接收id来判断是否相等
    bool operator==(const CMsg &other);
    CMsg &operator=(const CMsg &other);

    // 返回对应的变量值
    int get_send_id() const;
    int get_recv_id() const;
    char *get_msg_dt() const;
    char *get_content() const;
    void print();

    template <class Archive>
    void serialize(Archive & ar)
	{
		ar(cereal::make_nvp("_sendId", _sendId),
        cereal::make_nvp("_recvId", _recvId), 
        cereal::make_nvp("_msgDateTime",_msgDateTime), 
        cereal::make_nvp("_content",_content));
	}

private:
    int _sendId;
    int _recvId;
    std::string _msgDateTime;
    std::string _content;
};

#endif
