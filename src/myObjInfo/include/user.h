#ifndef __USER_H__
#define __USER_H__
#include <k_total_head.h>

/*用户功能暂定
    1.设置要素值
    2.用户同一个判断、用户赋值、获取各要素值
    3.不可单独修改某一个要素的值(需整个用户一起修改)
    by ks 2023-11-26

*/
class CUser
{

public:
    CUser();
    ~CUser();
    CUser(int userId,char *account,char *password,
        char* userName,int16_t userAge,char *currentIp,char *lastLeaveTime);
    //加入新用户时调用，其他时候不要使用该构造
    CUser(char *account,char *password,char* userName,int16_t userAge);
    CUser(const CUser &other);

    //为用户设置对应的值
    void set_user_info(int userId,char *account,char *password,
        char* userName,int16_t userAge,char *currentIp,char *lastLeaveTime);
    // 用account(账号)来判断是否相等
    bool operator==(const CUser &other);
    CUser &operator=(const CUser &other);

    // 设置id,其他的不允许单独设置
    void set_id(int id);

    // 返回对应的变量值
    int get_id() const;
    char *get_account() const;
    char *get_password() const;
    char *get_name() const;
    int16_t get_age() const;
    char * get_ip() const;
    char * get_leave_time() const;
    void print();

private:
    int _userId;
    char _account[7];
    char _password[16];
    char _userName[32];
    int16_t _userAge;
    char _currentIp[17];  //当前用户的登录ip
    char _lastLeaveTime[32]; //当前用户上一次的离开时间
};

#endif
