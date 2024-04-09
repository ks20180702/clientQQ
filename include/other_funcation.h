#ifndef __OTHER_FUNCATION_H__
#define  __OTHER_FUNCATION_H__

#include <chrono>
#include <iostream>

#include <memory>
#include <thread>


#include <mutex>                // 包含互斥锁的头文件
#include <condition_variable>   // 包含条件变量的头文件

std::string CurrentDate();

extern std::mutex mtx;                 // 定义互斥锁对象 mtx
extern std::mutex mtxFriendLists; 
extern std::mutex mtxMsgLists;
extern std::condition_variable cv;     // 定义条件变量对象 cv

#endif
