﻿#include <iostream>

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

    myCli.run();
    std::cout << myCli.get_error() << std::endl;
    
    std::cout<<"main over"<<std::endl;

}


