#include "./include/userChangeCmd.h"

CUserChangeCmd::CUserChangeCmd()
    :_operatorUser(){_childCmdType=USER_CHANGE_CMD;}


int CUserChangeCmd::do_command()
{
    // _childDoCommandReturn=false; //开始时，执行成功标记设置为false

    // int dealOperRe;
    // if(_operType==CHANGE_USER)
    // {
    //     dealOperRe=cmdOtlUse.change_user(_operatorUser);
    // }
    // else if(_operType==ADD_USER)
    // {
    //     dealOperRe=cmdOtlUse.add_user(_operatorUser);
    // }

    // if(dealOperRe==-1) {std::cout<<cmdOtlUse.get_errmsg()<<std::endl;return -1;}

    // _childDoCommandReturn=true;

    return 0;
}
std::string CUserChangeCmd::get_command_obj_json()
{
    std::ostringstream ss;
    cereal::JSONOutputArchive archiveOut(ss);
    archiveOut(cereal::make_nvp("logInfo._childCmdType", this->_childCmdType),cereal::make_nvp("logInfo", *this));

    return ss.str();
}


void CUserChangeCmd::set_operator_user(CUser &operatorUser)
{
    _operatorUser=operatorUser;
}
CUser CUserChangeCmd::get_operator_user()
{
    return _operatorUser;
}

void CUserChangeCmd::set_operator_type(OpratorType operType)
{
    _operType=operType;
}
CUserChangeCmd::~CUserChangeCmd()
{

}
