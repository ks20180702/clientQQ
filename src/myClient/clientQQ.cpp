#include "include/clientQQ.h"
#include "k_socket_include.h"

ClientQQ::ClientQQ()
    :_cliSoc(-1){FD_ZERO(&_globalFdset);}
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
int ClientQQ::select_init()
{
    FD_ZERO(&_globalFdset);
    // FD_SET(0,&_globalFdset); //加入标准输入
    FD_SET(_cliSoc,&_globalFdset);

    return 0;
}
int ClientQQ::run()
{
    fd_set currFdset;
    struct timeval timeout={3,0};
    char buf[SEND_RECV_BUF_SIZE]={0},inputDate[SEND_RECV_BUF_SIZE]={0};
    size_t r;

    int ndfsNum;
    int nfdsMax=_cliSoc; //其实客户端这里只有两个，且不会变，这样写只是为了看起来通用
    // int serLen=sizeof(_serAddr);


    while(1)
    {
        scanf("%s",inputDate);
        std::cout<<"1 is [loginCmd]"<<std::endl;
        std::cout<<"2 is [CHANGE_USER or add_user]"<<std::endl;
        std::cout<<"3 is [del friendShip or add friendShip ]"<<std::endl;
        param_input_cmd(inputDate);

        int serLen=sizeof(_serAddr);
        while(1)
        {
            int serLen=sizeof(_serAddr);
            currFdset=_globalFdset;
            
            if((ndfsNum=select(nfdsMax+1,&currFdset,NULL,NULL,&timeout))<0) {
                strcpy(_errMsg,"select error ");return -1;
            }
            if(ndfsNum==0) continue;

            for(int i=0;i<=nfdsMax;i++)
            {
                if(!FD_ISSET(i,&currFdset)) continue;

                if(i==_cliSoc) // 接收到服务端的数据
                {
                    FD_CLR(i,&currFdset);

                    memset(buf,0,SEND_RECV_BUF_SIZE);
                    r=recvfrom(_cliSoc,buf,SEND_RECV_BUF_SIZE,0,(struct sockaddr*)&_serAddr,&serLen);
                    if(r<0) {strcpy(_errMsg,"recvfrom error "); return -1;}

                    recv_cmd_part(buf,r);
                    if(strcmp(buf,"KS_END")==0){break;}
                }
            }
            if(strcmp(buf,"KS_END")==0){break;} //由于buf在此处还未清空，所以可以用来判断结束
        }  

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

        CUser myUser(1,(char*)"123456",(char*)"123456",(char*)"ks",23,"","2023-11-29 19:32:00");
        CLoginCmd logInfo(myUser);
        
        cmdJsonStr=logInfo.get_command_obj_json();
        send_part((char *)(cmdJsonStr.c_str()),cmdJsonStr.length(),true);

        _nowUseCmdObj=std::make_shared<CLoginCmd>(logInfo);
    }
    else if(strcmp(inputBuf,"2")==0)
    {
        std::cout<<"[input == 2] run user change "<<std::endl;

        CUser myUser(1,(char*)"141414",(char*)"123456",(char*)"ks_13",23,"","2023-11-29 19:32:00");
        CUserChangeCmd userChangeCmd;
        userChangeCmd.set_operator_user(myUser);
        //数据库操作修改用户信息好像有点问题，不报错但是没反应
        userChangeCmd.set_operator_type(CUserChangeCmd::CHANGE_USER);
        // userChangeCmd.set_operator_type(CUserChangeCmd::ADD_USER);

        cmdJsonStr=userChangeCmd.get_command_obj_json();

        send_part((char *)(cmdJsonStr.c_str()),cmdJsonStr.length(),true);

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
    else{
        send_part(inputBuf,sizeof(inputBuf),true);

        std::cout<<inputBuf<<std::endl;
    }
    return 0;
}

int ClientQQ::recv_cmd_part(char *buf,int readNum)
{
    //是否开始接收，当接收到开始标志(KS_START)表示开始接收整条语句
    static bool cmdStrOver=false;
    static std::string tempStr="";

    if(cmdStrOver==true)
    {
        if (strcmp(buf,"KS_END")==0)
        {
            std::cout<<"tempStr cmd =  "<<tempStr.length()<<std::endl;
            param_cmd_str(tempStr);

            cmdStrOver=false;
            tempStr="";
        }
        else
        {
            tempStr+=std::string(buf,readNum);
        }
    }
    else
    {
        // 接收结构体
        if(strcmp(buf,"KS_START")==0)
        {
            cmdStrOver=true;
            tempStr="";
        }
        else
        {
            std::cout<<"recv from : "<<buf<<std::endl;
        }
    }
    return 0;
}

int ClientQQ::param_cmd_str(std::string cmdStr)
{
    std::cout<<"++++++++++++++++++++"<<std::endl;
    std::cout<<cmdStr<<"\n}"<<std::endl;
    std::cout<<"++++++++++++++++++++"<<std::endl;

    // CmdBase::CmdType childCmdType;

	_nowUseCmdObj->reload_recv_obj_by_str(cmdStr);

    _nowUseCmdObj->show_do_command_info();
    std::cout<<"return mess:"<<_nowUseCmdObj->_childDoCommandReturn<<std::endl;

    return 0;
}

int ClientQQ::send_part(char *sendStr,int n,bool isCmd)
{
    size_t w;
    char *sendTemp=sendStr;
    int nowNum=0,sendLen;
    
    if(isCmd==true)
    {
        w=sendto(_cliSoc,"KS_START",sizeof("KS_START"),0,(struct sockaddr*)&_serAddr,sizeof(_serAddr));
        if(w<0) {strcpy(_errMsg,"send error"); return -1;}
    }

    while(nowNum<n)
    {
        if((n-nowNum)>=SEND_RECV_BUF_SIZE)
        {
            sendLen=SEND_RECV_BUF_SIZE;
        }
        else{
            sendLen=n-nowNum;
        }
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
