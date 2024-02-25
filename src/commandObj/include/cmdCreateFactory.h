#ifndef __CMDCREATEFACTORY_H__
#define __CMDCREATEFACTORY_H__

/*
    创建指定对象的工厂类
*/

#include "k_total_head.h"
#include "cmdBase.h"

class CmdCreateFactory
{

/*
    暂时考虑每次都创建一个新的(一个类创建的对象应该不会使用第二次)，所以不使用map保存
*/
public:
    CmdCreateFactory(){};
    ~CmdCreateFactory(){};

    CmdBase* create_cmd_ptr(CmdBase::CmdType inputCmdType);

};

#endif