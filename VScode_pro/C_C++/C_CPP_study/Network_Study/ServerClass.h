#ifndef _SERVERCLASS_
#define _SERVERCLASS_


#include <winsock2.h>
#include <iostream>
#include <string>
#include <thread>
#include <map>

using namespace std;
#pragma comment(lib, "ws2_32.lib") 
//防止头文件重复包含
// #pragma  once
//兼容C++编译器
//如果是C++编译器，按c标准编译
// #ifdef __cplusplus
// extern "C"
// {

// #endif
class ServerSocket{

public:
    bool OpenWSA();
    void CloseWSA();
    bool CreateSocketAndConnect();
    ServerSocket();
    int SetsockVersion(WORD version);
    int SetsockAddr(sockaddr_in addr);
    int Setserversocket(SOCKET socket);
    SOCKET Getserversocket();
    int CreateSocketAndAddr();

// private:
    WORD sockVersion;
    WSADATA wsdata;

    SOCKET serverSocket;
    sockaddr_in sockAddr;

};


#endif