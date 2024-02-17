#include <iostream>

using namespace std;
#include "user.h"
#include "otlUse.h"
#include "cmdBase.h"
#include "loginCmd.h"
#include "userChangeCmd.h"
void test(CmdBase *base)
{
	base->do_command();
}
int main()
{
	std::cout<<"main +++"<<std::endl;

	std::shared_ptr<CmdBase> testBase;

	CUser myUser(10,(char*)"123456",(char*)"123456",(char*)"ks",23,"","2023-11-29 19:32:00");
	CUser myUserAdd((char*)"115555",(char*)"123456",(char*)"add",23);
	CLoginCmd loginCmd;
	loginCmd.set_login_user(myUser);
	(loginCmd.get_login_user()).print();

	testBase=loginCmd.get_next_command();
	testBase->do_command();
	if(testBase->get_next_command()==nullptr) std::cout<<"is nullptr"<<std::endl;
	return 0;

	CUserChangeCmd userChangeCmd;
	userChangeCmd.set_operator_type(CUserChangeCmd::ADD_USER);
	userChangeCmd.set_operator_user(myUserAdd);
    test(&userChangeCmd);

	COtlUse otlUse;
	otlUse.olt_init();
	otlUse.set_user_id_by_account(myUserAdd);
	myUserAdd.print();
	std::cout<<"end +++"<<std::endl;
	return 0;// int selectReturn;
}


