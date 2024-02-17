#ifndef __MSG_H__
#define __MSG_H__
#include <k_total_head.h>

/*消息对象

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

private:
    int _sendId;
    int _recvId;
    char _msgDateTime[32];
    char _content[512];
};

#endif
