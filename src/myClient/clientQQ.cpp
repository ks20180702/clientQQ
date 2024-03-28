#include "./include/clientQQ.h"
#include "k_clip.h"

// extern string Utf8ToGbk(const char *src_str);

ClientQQ::ClientQQ()
    :_cliSoc(-1),_cmdStr(""){}


int ClientQQ::client_init(const char *ipAddr)
{
    WSADATA WSAData;
    if (WSAStartup(MAKEWORD(2, 2), &WSAData))
    {
        strcpy(_errMsg,"initializationing error!\n");
        WSACleanup();
        return -1;
    }

    if ((_cliSoc = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        strcpy(_errMsg,"创建套接字失败!\n");
        WSACleanup();
        return -1;
    }

    _cliSoc=socket(AF_INET,SOCK_DGRAM,0);
    if(_cliSoc==-1) {strcpy(_errMsg,"socket create "); return -1;}

    _serAddr.sin_family=AF_INET;
    _serAddr.sin_port=htons(SERVER_PORT);
    _serAddr.sin_addr.s_addr=inet_addr(ipAddr);
    //    inet_pton(AF_INET,ipAddr,&(_serAddr.sin_addr));

    std::thread recvThread(&ClientQQ::pthread_recv_data,this,_cliSoc,_serAddr);
    recvThread.detach();

    return 0;
}

void ClientQQ::pthread_recv_data(const int cliSoc,const struct sockaddr_in serAddr)
{
    struct timeval timeout={3,0};
    char buf[SEND_RECV_BUF_SIZE]={0};
    size_t r;int ndfsNum;
    int serLen=sizeof(serAddr);
    
    //其实客户端这里只有一个，且不会变，这样写只是为了看起来通用
    fd_set globalFdset;
    FD_ZERO(&globalFdset);

    while(1)
    {
        FD_SET(cliSoc,&globalFdset); //相当于重新监控该socketid,如果不加，则在清除一遍后不会再监听了
        if((ndfsNum=select(cliSoc+1,&globalFdset,NULL,NULL,&timeout))<0) {
            strcpy(_errMsg,"select error ");return ;
        }
        if(ndfsNum==0) continue;

        // FD_CLR(_cliSoc,&globalFdset); //待测试，应该可以删除的
        memset(buf,0,SEND_RECV_BUF_SIZE);
        r=recvfrom(cliSoc,buf,SEND_RECV_BUF_SIZE,0,(struct sockaddr*)&serAddr,&serLen);
        if(r<0) {strcpy(_errMsg,"recvfrom error "); return ;}

        recv_cmd_part(buf,r);
    }  
}
int ClientQQ::recv_cmd_part(char *buf,int readNum)
{
    // 接收结构体
    if(strcmp(buf,"KS_START")==0){_cmdStr="";}
    else if(strcmp(buf,"KS_END")==0)
    {
        std::shared_ptr<CmdCreateFactory> factoryCreater=std::make_shared<CmdCreateFactory>();

        //设置childCmdType
        CmdBase::CmdType childCmdType;
        std::istringstream istrStream(_cmdStr+CMD_STR_ADD);
        cereal::JSONInputArchive jsonIA(istrStream);
        jsonIA(cereal::make_nvp("_childCmdType", childCmdType));

        //为对应的指针对象初始化
        std::shared_ptr<CmdBase> useCmdObj=shared_ptr<CmdBase>(factoryCreater->create_cmd_ptr(childCmdType));
        useCmdObj->reload_recv_obj_by_json(jsonIA);      
        useCmdObj->show_do_command_info();

        //加入到待查看指令中(主要为带聊天记录的数据指令)
        _cmdPtrLists.push_front(useCmdObj);
 
        _cmdStr="";
    }
    //这里稍微有个问题就是，一直接收不到KS_START,但一直接收数据，导致字符串过大。待后续处理
    else{_cmdStr+=std::string(buf,readNum);} 
    return 0;
}

int ClientQQ::send_login_cmd(CUser &loginUser)
{
    // CUser loginUser(1,"123456","123456","",23,"","2023-11-29 19:32:00");
    
    std::string cmdJsonStr;
    CLoginCmd logInfo(loginUser);
    
    cmdJsonStr=logInfo.get_command_obj_json();
    return send_main_part(cmdJsonStr,cmdJsonStr.length());
}
int ClientQQ::send_user_change_cmd(CUser &myUser,CUserChangeCmd::OpratorType operType)
{
    // CUser myUser(1,(char*)"151515",(char*)"123456",(char*)"ks_15",23,"","2023-11-29 19:32:00");

    std::string cmdJsonStr;

    CUserChangeCmd userChangeCmd;
    userChangeCmd.set_operator_user(myUser);
    userChangeCmd.set_operator_type(operType); //CUserChangeCmd::CHANGE_USER/ADD_USER

    cmdJsonStr=userChangeCmd.get_command_obj_json();

    return send_main_part(cmdJsonStr,cmdJsonStr.length());
}
int ClientQQ::send_friendship_change_cmd(CUser &myUser,CUser &userFriend,CFriendshipChangeCmd::OperatorFriendShipType shipOperType)
{
    // CUser user1((char*)"141414",(char*)"123456",(char*)"ks_14",23);
    // CUser userFriend((char*)"131313",(char*)"123456",(char*)"ks_13",23);

    std::string cmdJsonStr;
    CFriendshipChangeCmd friendShipChange;

    friendShipChange.set_user(myUser);
    friendShipChange.set_friend_user(userFriend);
    friendShipChange.set_operator_type(shipOperType);

    cmdJsonStr=friendShipChange.get_command_obj_json();

    return send_main_part(cmdJsonStr,cmdJsonStr.length());
}
int ClientQQ::send_heart_cmd(CUser &currentUser)
{
    // CUser currentUser("222222","123456","",0);

    std::string cmdJsonStr;

    CHeartRequestCmd heartCmd(currentUser);
    cmdJsonStr=heartCmd.get_command_obj_json();
    return send_main_part(cmdJsonStr,cmdJsonStr.length());
}
int ClientQQ::send_main_part(std::string &cmdJsonStr,int n)
{
    size_t w;   
    int nowNum=0,sendLen;
    char *sendTemp=(char *)(cmdJsonStr.c_str());

    //有一个问题，先发送的数据不一定先到达
    //发送开始标记
    w=sendto(_cliSoc,"KS_START",sizeof("KS_START"),0,(struct sockaddr*)&_serAddr,sizeof(_serAddr));
    if(w<0) {strcpy(_errMsg,"send error"); return -1;}
    Sleep(50); 

    //发送指定字节流
    while(nowNum<n)
    {
        //未发送字符大于1024，发送1024，否则发送剩下的
        if((n-nowNum)>=SEND_RECV_BUF_SIZE){sendLen=SEND_RECV_BUF_SIZE;}
        else{sendLen=n-nowNum;}

        w=sendto(_cliSoc,sendTemp+nowNum,sendLen,0,(struct sockaddr*)&_serAddr,sizeof(_serAddr));
        Sleep(50);
        if(w<0) {strcpy(_errMsg,"send error"); return -1;}

        nowNum+=w;
    }

    //发送结束标记
    w=sendto(_cliSoc,"KS_END",sizeof("KS_END"),0,(struct sockaddr*)&_serAddr,sizeof(_serAddr));
    if(w<0) {strcpy(_errMsg,"send error"); return -1;}


    return 0;
}

std::list<std::shared_ptr<CmdBase>>& ClientQQ::get_cmd_ptr_lists()
{  
   return _cmdPtrLists; 
}
char *ClientQQ::get_error()
{
    return (char*)_errMsg;
}

//显示上一个错误的错误详情
void ClientQQ::show_error_detail()
{
    perror(_errMsg);
}

int& ClientQQ::get_socket()
{
    return _cliSoc;
}

ClientQQ::~ClientQQ()
{
    closesocket(_cliSoc);
    WSACleanup();
//    close(_cliSoc);
}
