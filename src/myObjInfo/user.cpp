#include "./include/user.h"


CUser::CUser()
    :_userId(0),_account(""),_password(""),
    _userName(""),_userAge(0),_currentIp(""),_lastLeaveTime(""){}

CUser::CUser(int userId,char *account,char *password,
        char* userName,int16_t userAge,char *currentIp,char *lastLeaveTime)
{
    this->set_user_info(userId,account,password,userName,userAge,currentIp,lastLeaveTime);
}
CUser::CUser(char *account,char *password,char* userName,int16_t userAge)
{
    this->set_user_info(0,account,password,userName,userAge,"","");
}
CUser::CUser(const CUser &other)
{
    *this=other;
}

void CUser::set_user_info(int userId,char *account,char *password,
    char* userName,int16_t userAge,char *currentIp,char *lastLeaveTime)
{
    //此处需加一个长度检查
    
    _userId=userId;
    strcpy(_account,account);
    strcpy(_password,password);
    strcpy(_userName,userName);
    _userAge=userAge;
    strcpy(_currentIp,currentIp);
    strcpy(_lastLeaveTime,lastLeaveTime);
}
void CUser::set_id(int id)
{
    _userId=id;
}

int CUser::get_id() const
{
    return _userId;
}
char *CUser::get_account() const
{
    return (char*)_account;
}
char *CUser::get_password() const
{
    return (char*)_password;
}
char *CUser::get_name() const
{
    return (char*)_userName;
}   
int16_t CUser::get_age() const
{
    return _userAge;
}
char * CUser::get_ip() const
{
    return (char*)_currentIp;
}
char *CUser::get_leave_time() const
{
    return (char*)_lastLeaveTime;
}
void CUser::print()
{
    std::cout<<"id = "<<this->get_id();
    std::cout<<"; account = "<<this->get_account();
    std::cout<<"; password = "<<this->get_password();
    std::cout<<"; name = "<<this->get_name();
    std::cout<<"; age = "<<this->get_age();
    std::cout<<"; ip = "<<this->get_ip();
    std::cout<<"; last leave time = "<<this->get_leave_time()<<std::endl;
}
bool CUser::operator==(const CUser &other)
{
    if(strcmp(_account,other.get_account())==0) return true;
    else return false;
}
CUser &CUser::operator=(const CUser &other)
{
    this->set_user_info(other.get_id(),other.get_account(),other.get_password(),
                        other.get_name(),other.get_age(),other.get_ip(),other.get_leave_time());

    return *this;
}

CUser::~CUser()
{
}