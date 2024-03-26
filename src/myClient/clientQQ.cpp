#include "./include/clientQQ.h"
#include "k_clip.h"

ClientQQ::ClientQQ()
    :_cliSoc(-1),_cmdStr(""){}
int ClientQQ::client_init(char *ipAddr)
{

    WSADATA WSAData;
    if (WSAStartup(MAKEWORD(2, 2), &WSAData))
    {
        printf("initializationing error!\n");
        WSACleanup();
        return -1;
    }

    if ((_cliSoc = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        printf("创建套接字失败!\n");
        WSACleanup();
        return -1;
    }

    _cliSoc=socket(AF_INET,SOCK_DGRAM,0);
    if(_cliSoc==-1) {strcpy(_errMsg,"socket create "); return -1;}

    _serAddr.sin_family=AF_INET;
    _serAddr.sin_port=htons(SERVER_PORT);
//    inet_pton(AF_INET,ipAddr,&(_serAddr.sin_addr));
    _serAddr.sin_addr.s_addr=inet_addr(ipAddr);

    return 0;
}

int ClientQQ::run()
{
    struct timeval timeout={3,0};
    char buf[SEND_RECV_BUF_SIZE]={0},inputDate[SEND_RECV_BUF_SIZE]={0};
    size_t r;

    int ndfsNum;
    int serLen=sizeof(_serAddr);
    
    //其实客户端这里只有一个，且不会变，这样写只是为了看起来通用
    fd_set globalFdset;
    FD_ZERO(&globalFdset);
    while(1)
    {
        scanf("%s",inputDate);
        // inputDate[0]='1';
        std::cout<<"1 is [loginCmd]"<<std::endl;
        std::cout<<"2 is [CHANGE_USER or add_user]"<<std::endl;
        std::cout<<"3 is [del friendShip or add friendShip ]"<<std::endl;
        param_input_cmd(inputDate);

        while(1)
        {
            FD_SET(_cliSoc,&globalFdset); //相当于重新监控该socketid,如果不加，则在清除一遍后不会再监听了
            if((ndfsNum=select(_cliSoc+1,&globalFdset,NULL,NULL,&timeout))<0) {
                strcpy(_errMsg,"select error ");return -1;
            }
            if(ndfsNum==0) continue;

            // FD_CLR(_cliSoc,&globalFdset); //代测试，应该可以删除的
            memset(buf,0,SEND_RECV_BUF_SIZE);
            r=recvfrom(_cliSoc,buf,SEND_RECV_BUF_SIZE,0,(struct sockaddr*)&_serAddr,&serLen);
            if(r<0) {strcpy(_errMsg,"recvfrom error "); return -1;}

            recv_cmd_part(buf,r);
        }  
        break;
    }
}
int ClientQQ::param_input_cmd(char *inputBuf)
{
    //将当前的指令对象指向null
    if(nullptr!= _nowUseCmdObj)
    {
        _nowUseCmdObj=nullptr;
    }

    std::string cmdJsonStr;
    if(strcmp(inputBuf,"1")==0)
    {
        std::cout<<"[input == 1] run login "<<std::endl;

        CUser myUser(1,"123456","123456","",23,"","2023-11-29 19:32:00");
        CLoginCmd logInfo(myUser);
        
        cmdJsonStr=logInfo.get_command_obj_json();
        send_part((char *)(cmdJsonStr.c_str()),cmdJsonStr.length(),true);

        _nowUseCmdObj=std::make_shared<CLoginCmd>(logInfo);
    }
    else if(strcmp(inputBuf,"2")==0)
    {
        std::cout<<"[input == 2] run user change "<<std::endl;

        CUser myUser(1,(char*)"151515",(char*)"123456",(char*)"ks_15",23,"","2023-11-29 19:32:00");
        CUserChangeCmd userChangeCmd;
        userChangeCmd.set_operator_user(myUser);
        //数据库操作修改用户信息好像有点问题，不报错但是没反应
        // userChangeCmd.set_operator_type(CUserChangeCmd::CHANGE_USER);
        userChangeCmd.set_operator_type(CUserChangeCmd::ADD_USER);

        cmdJsonStr=userChangeCmd.get_command_obj_json();

        send_part((char *)(cmdJsonStr.c_str()),cmdJsonStr.length(),true);

        std::cout<<cmdJsonStr.c_str()<<std::endl;
        _nowUseCmdObj=std::make_shared<CUserChangeCmd>(userChangeCmd);
    }
    else if(strcmp(inputBuf,"3")==0)
    {
        std::cout<<"[input == 3] run user change "<<std::endl;

        CUser user1((char*)"141414",(char*)"123456",(char*)"ks_14",23);
        CUser userFriend((char*)"131313",(char*)"123456",(char*)"ks_13",23);
        CFriendshipChangeCmd friendShipChange;

        friendShipChange.set_user(user1);
        friendShipChange.set_friend_user(userFriend);
        friendShipChange.set_operator_type(CFriendshipChangeCmd::DELETT_FRIEND);

        cmdJsonStr=friendShipChange.get_command_obj_json();

        send_part((char *)(cmdJsonStr.c_str()),cmdJsonStr.length(),true);

        _nowUseCmdObj=std::make_shared<CFriendshipChangeCmd>(friendShipChange);
    }
    else if(strcmp(inputBuf,"4")==0)
    {
        std::cout<<"[input == 4] heart cmd "<<std::endl;

        CUser currentUser("222222","123456","",0);
        CHeartRequestCmd heartCmd(currentUser);

        cmdJsonStr=heartCmd.get_command_obj_json();

        send_part((char *)(cmdJsonStr.c_str()),cmdJsonStr.length(),true);

        _nowUseCmdObj=std::make_shared<CHeartRequestCmd>(heartCmd);
    }
    else{
        send_part(inputBuf,sizeof(inputBuf),true);
    }
    return 0;
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
        std::istringstream istrStream(Utf8ToGbk(_cmdStr.c_str())+CMD_STR_ADD);
        cereal::JSONInputArchive jsonIA(istrStream);
        jsonIA(cereal::make_nvp("_childCmdType", childCmdType));

        std::shared_ptr<CmdBase> useCmdObj=shared_ptr<CmdBase>(factoryCreater->create_cmd_ptr(childCmdType));
        useCmdObj->reload_recv_obj_by_json(jsonIA);      
        useCmdObj->show_do_command_info();
 
        _cmdStr="";
    }
    //这里稍微有个问题就是，一直接收不到KS_START,但一直接收数据，导致字符串过大。待后续处理
    else{_cmdStr+=std::string(buf,readNum);} 
    return 0;
}

int ClientQQ::send_part(char *sendStr,int n,bool isCmd)
{
    size_t w;
    char *sendTemp=sendStr;
    std::cout<<sendStr<<std::endl;
    int nowNum=0,sendLen;
    
    //有一个问题，先发送的数据不一定先到达
    if(isCmd==true)
    {
        w=sendto(_cliSoc,"KS_START",sizeof("KS_START"),0,(struct sockaddr*)&_serAddr,sizeof(_serAddr));
        if(w<0) {strcpy(_errMsg,"send error"); return -1;}
    }
    Sleep(50); 

    //发送指定字节流
    while(nowNum<n)
    {
        //未发送字符大于1024，发送1024，否则发送剩下的
        if((n-nowNum)>=SEND_RECV_BUF_SIZE){sendLen=SEND_RECV_BUF_SIZE;}
        else{sendLen=n-nowNum;}

        w=sendto(_cliSoc,sendTemp+nowNum,sendLen,0,(struct sockaddr*)&_serAddr,sizeof(_serAddr));
        if(w<0) {strcpy(_errMsg,"send error"); return -1;}

        nowNum+=w;
    }
    if(isCmd==true)
    {
        w=sendto(_cliSoc,"KS_END",sizeof("KS_END"),0,(struct sockaddr*)&_serAddr,sizeof(_serAddr));
        if(w<0) {strcpy(_errMsg,"send error"); return -1;}
    }

    return 0;
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
