#include "other_funcation.h"

using sysclock_t = std::chrono::system_clock;

std::string CurrentDate()
{
    std::time_t now = sysclock_t::to_time_t(sysclock_t::now());

    char buf[16] = { 0 };
    std::strftime(buf, sizeof(buf), "%Y-%m-%d", std::localtime(&now));

    return std::string(buf);
}

std::mutex mtx;                 // 定义互斥锁对象 mtx
std::mutex mtxFriendLists;                 // 定义互斥锁对象 mtx
std::mutex mtxMsgLists;
std::condition_variable cv;     // 定义条件变量对象 cv
