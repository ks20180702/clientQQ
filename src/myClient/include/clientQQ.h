#ifndef __CLIENTQQ_H__
#define __CLIENTQQ_H__

#include "k_socket_include.h"
#include "k_total_head.h"
#include "loginCmd.h"
#include "userChangeCmd.h"
#include "friendshipChangeCmd.h"
#include "heartRequestCmd.h"
#include "cmdCreateFactory.h"

#include <vector>
#include <list>
#include <memory>
#include <thread>

/*
    win下的select不支持将标准输入加入，之前的代码有点不通用，
    这里在run中改成win下版本
*/
class ClientQQ
{
public:
    ClientQQ();
    ~ClientQQ();

    //获取socket，连接指定的ip
    //错误-1，成功0
    int client_init(const char *ipAddr);

    //接收线程函数，用户接收服务器端发送过来的数据
    void thread_recv_data(const int cliSoc,const struct sockaddr_in serAddr);
    //按指定协议分批接收数据
    //错误-1，成功0
    int recv_cmd_part(char *buf,int readNum);

    //发送心跳包的线程，暂定10秒发送一次。(传的是引用，所以若用户修改密码后，还是没问题，可以正确验证的)
    void heart_thread_init(CUser &currentUser);
    void thread_send_heart_cmd(CUser &currentUser);

    //发送登录指令//错误-1，成功0
    int send_login_cmd(CUser &loginUser);
    //发送登录指令//错误-1，成功0
    int send_data_msg_cmd(Cuser &recvUser,CMsg &dataMsg,CDataMsgCmd::MsgRequestType requestType);
    //发送用户信息修改指令//错误-1，成功0
    int send_user_change_cmd(CUser &myUser,CUserChangeCmd::OpratorType operType);
    //发送好友关系修改指令//错误-1，成功0
    int send_friendship_change_cmd(CUser &myUser,CUser &userFriend,CFriendshipChangeCmd::OperatorFriendShipType shipOperType);
    //发送心跳包指令//错误-1，成功0
    int send_heart_cmd(CUser &currentUser);
    //分批发送数据，暂定1024//错误-1，成功0
    int send_main_part(std::string &cmdJsonStr,int n);



    //返回当前未处理的指令对象
    std::list<std::shared_ptr<CmdBase>>& get_cmd_ptr_lists();

    char *get_error();

    //显示上一个错误的错误详情
    void show_error_detail();

    int& get_socket();

private:
    char _errMsg[128]="OK";

    int _cliSoc;struct sockaddr_in _serAddr;

    //这里可能需要再增加一个一样的list,并增加锁，防止一边遍历一边增加指令指针。
    //等后面处理聊天数据的时候再增加
    //指向指令对象的list
    std::list<std::shared_ptr<CmdBase>> _cmdPtrLists;

    std::string  _cmdStr;
};


#endif
