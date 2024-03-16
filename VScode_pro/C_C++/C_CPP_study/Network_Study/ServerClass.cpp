#include "ServerClass.h"
using namespace std;
// #pragma comment(lib, "ws2_32.lib") 

// 定义端口号
#define PORT 8080

ServerSocket::ServerSocket(){
    sockVersion = MAKEWORD(2, 2);
}


int ServerSocket::CreateSocketAndAddr(){
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET){
        cout << "Socket error" << endl;
        system("pause");
        return 0;
    }  
    sockAddr.sin_family = AF_INET;
    sockAddr.sin_port = htons(PORT);
    sockAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    return 1;
}

bool ServerSocket::CreateSocketAndConnect(){

    if (bind(serverSocket, (sockaddr*)&sockAddr, sizeof(sockAddr)) == SOCKET_ERROR){
        cout << "Bind error" << endl;
        system("pause");
        return false;
    }

    //开始监听
    if (listen(serverSocket, 10) == SOCKET_ERROR){
        cout << "Listen error" << endl;
        system("pause");
        return false;
    }

    return true;
}

bool ServerSocket::OpenWSA(){
    if (WSAStartup(sockVersion, &wsdata) != 0){
        cout << "WSAStartup error" << endl;
        system("pause");
        return false;
    }
    return true;
}

void ServerSocket::CloseWSA(){
    WSACleanup();
}

int ServerSocket::Setserversocket(SOCKET socket){
    serverSocket = socket;
    return 1;
}

int ServerSocket::SetsockAddr(sockaddr_in addr){
    sockAddr = addr;
    return 1;
}

int ServerSocket::SetsockVersion(WORD version){
    sockVersion = version;
    return 1;
}

SOCKET ServerSocket::Getserversocket(){
    return serverSocket;
}