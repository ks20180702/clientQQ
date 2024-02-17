#include <iostream>

using namespace std;
#include "user.h"
#include "otlUse.h"
#include "cmdBase.h"
#include "loginCmd.h"
#include "userChangeCmd.h"
#include "msg.h"
#include "dataCmd.h"

#include "userNotRecvMsg.h"
using namespace std;
	
int main()
{
	std::cout<<"main +++"<<std::endl;

	COtlUse myOtlUse;
	CUser user1("123456","123456","",0);
	vector<CUserNotRecvMsg> userNotRecvMsgs;
	int recvRe;

	myOtlUse.olt_init();
	myOtlUse.set_user_id_by_account(user1);
	myOtlUse.get_user_by_id(user1.get_id(),user1);
	user1.print();
	
	recvRe=myOtlUse.get_user_not_recv_msg_info(user1.get_id(),userNotRecvMsgs);
	if(recvRe==-1) std::cout<<myOtlUse.get_errmsg()<<std::endl;

	for(vector<CUserNotRecvMsg>::iterator it=userNotRecvMsgs.begin();it!=userNotRecvMsgs.end();it++)
	{
		it->print();
	}
}


