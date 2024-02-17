#include <iostream>

using namespace std;
#include "user.h"
#include "cmdBase.h"
#include "loginCmd.h"
#include "userChangeCmd.h"
#include "msg.h"
#include "dataCmd.h"

#include "userNotRecvMsg.h"
#include "clientQQ.h"

using namespace std;

int main()
{
    std::cout<<"main +++"<<std::endl;

    ClientQQ myCli;
    myCli.client_init("192.168.47.136");
    myCli.select_init();

    CUser myUser(10,(char*)"123456",(char*)"123456",(char*)"ks",23,"","2023-11-29 19:32:00");
    CLoginCmd logInfo(myUser);

    std::vector<CUser> myTest;
    for(int i=0;i<10;i++)
    {
        CUser myUser(i,(char*)"123456",(char*)"123456",(char*)"ks",23,"","2023-11-29 19:32:00");
        myTest.push_back(myUser);
    }
    logInfo.set_friend_lists(myTest);

    std::ostringstream ss;
	cereal::JSONOutputArchive archive(ss);
	archive(cereal::make_nvp("logInfo", logInfo),cereal::make_nvp("logInfo._childCmdType", logInfo._childCmdType));
    std::cout<<logInfo._childCmdType<<std::endl;
    std::cout<<ss.str()<<std::endl;

    std::cout<<sizeof(ss.str())<<std::endl;
    std::cout<<ss.str().length()<<std::endl;

    // myCli.run((char *)(ss.str().c_str()),ss.str().length());
    myCli.run();
    myCli.show_error_detail();
    
    std::cout<<"main over"<<std::endl;
}


