#include "./include/userChangeCmd.h"

CUserChangeCmd::CUserChangeCmd()
    :_operatorUser(){_childCmdType=USER_CHANGE_CMD;}


int CUserChangeCmd::do_command(COtlUse &cmdOtlUse)
{
    return 0;
}
std::string CUserChangeCmd::get_command_obj_json()
{
    std::ostringstream ostrStream;
    cereal::JSONOutputArchive jsonOA(ostrStream);
    super_json_add_make_nvp(jsonOA,this->_childCmdType);
    
    jsonOA(cereal::make_nvp("userChangeInfo", *this));
    return ostrStream.str();
}

void CUserChangeCmd::reload_recv_obj_by_json(cereal::JSONInputArchive &jsonIA) 
{
    jsonIA(cereal::make_nvp("userChangeInfo", *this));
}

void CUserChangeCmd::show_do_command_info()
{
    if(CHANGE_USER==_operType)
    {
        if(!_childDoCommandReturn)
        {
            std::cout<<"[E]  修改用户信息失败"<<std::endl;
            return ;
        }
        std::cout<<"[I]  用户修改成功，用户信息如下："<<std::endl;
    }
    else if(ADD_USER==_operType)
    {
        if(!_childDoCommandReturn)
        {
            std::cout<<"[E]  添加用户信息失败"<<std::endl;
            return ;
        }
        std::cout<<"[I]  添加用户成功，用户信息如下："<<std::endl;
    }
    _operatorUser.print();
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
