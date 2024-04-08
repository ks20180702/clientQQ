#ifndef __K_SOCKET_INCLUDE_H__
#define __K_SOCKET_INCLUDE_H__

#ifdef _WIN32
//    #define WIN32_LEAN_AND_MEAN
    #include<winsock.h>
    #include<windows.h>
    #include<stdio.h>
    #include<stdlib.h>
    #include<string.h>
    #include<iostream>
    //#include<WinSock2.h>
//    #include<ws2tcpip.h>
    #pragma comment( lib, "ws2_32.lib" )
#else
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <netinet/ip.h>
    #include <sys/types.h>
    #include <arpa/inet.h>
    #include <unistd.h>
#endif

#define SERVER_PORT 7070
#define CLIEND_PORT 7071
#define SEND_RECV_BUF_SIZE 1024

#define SERVER_ADDR "114.55.229.106"
#endif
