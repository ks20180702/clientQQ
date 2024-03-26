#include <iostream>

/*
    win版本下的客户端源码
*/
using namespace std;
#include "user.h"
#include "cmdBase.h"
#include "loginCmd.h"
#include "userChangeCmd.h"
#include "msg.h"

#include "userNotRecvMsg.h"
#include "clientQQ.h"

using namespace std;

int main()
{
    std::cout<<"main +++"<<std::endl;

    ClientQQ myCli;
    //myCli.client_init("192.168.47.135");
    myCli.client_init("114.55.229.106");
    
    // //登录指令测试
    // CUser loginUser(1,"123456","123456","",23,"","2023-11-29 19:32:00");
    // myCli.send_login_cmd(loginUser);
    // Sleep(100);

    //用户信息修改指令测试
    CUser myUser(1,(char*)"151515",(char*)"123456",(char*)"ks_995",23,"","2023-11-29 19:32:00");
    myCli.send_user_change_cmd(myUser,CUserChangeCmd::CHANGE_USER);
    Sleep(100);

    // //好友关系修改指令测试
    // CUser user1((char*)"141414",(char*)"123456",(char*)"ks_14",23);
    // CUser userFriend((char*)"131313",(char*)"123456",(char*)"ks_13",23);
    // //待增加
    // myCli.send_friendship_change_cmd(user1,userFriend,CFriendshipChangeCmd::DELETT_FRIEND);
    // Sleep(100);

    //心跳指令测试
    CUser currentUser("222222","123456","",0);
    myCli.send_heart_cmd(currentUser);
    Sleep(100);

    std::cout << myCli.get_error() << std::endl;

    while (1)
    {
        /* code */
    }
    std::cout<<"main over"<<std::endl;

}


