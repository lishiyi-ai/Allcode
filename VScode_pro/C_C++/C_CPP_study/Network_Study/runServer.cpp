#include <winsock2.h>
#include <iostream>
#include <string>
#include <thread>
#include <map>
// #include "ServerClass.h"
#include "ServerClass.cpp"

using namespace std;
#pragma comment(lib, "ws2_32.lib") 

// 存放在线客户端
map<string, SOCKET> clientsockets;

void getnameAndinfo(char msg[], int num, string &name, string &text);
void RecAndSend(string name, SOCKET clientsocket);

void getnameAndinfo(char msg[], int num, std::string &name, std::string &text){
    // 获取发送者昵称
    int i = 0;
    for(i = 0; i < num; ++i){
        if(msg[i] == ' ') break;
        name += msg[i];
    }

    ++i;
    // 获取消息文本
    for(i; i < num ; ++i){
        text +=msg[i];
    }

    return;
}

// 接受客户段消息并进行转发
void RecAndSend(string name, SOCKET clientsocket){
    char msg[1024]; 
    while(true){
        int num = recv(clientsocket, msg, 1024, 0);
        // 发送的为空报文表示该客户端已经关闭
        cout<<"收到信息"<<endl;
        if(num <= 0){
            cout<<"客户端:"<<name<<"已经关闭"<<endl;
            closesocket(clientsocket);
            clientsockets.erase(name);
            return;
        }

        string name1;
        string msg1;
        msg[num] = '\0';
        getnameAndinfo(msg, num, name1, msg1);
        // cout << name1 << " say: "<< msg1 << endl;
        if(clientsockets.find(name1)==clientsockets.end()){
            send(clientsocket, "server 该好友不在线", strlen("server 该好友不在线"), 0);
            continue;
        }
        SOCKET socket = clientsockets[name1];
        const char * sendData;
        sendData = msg;
        cout<<"sendData"<<sendData<<endl;
        send(socket, sendData, strlen(sendData), 0);
        cout<<"发送完成"<<endl;
    }
    return;
}

int main(int argc, char *argv[]){
    ServerSocket socket = ServerSocket();
    if(socket.OpenWSA() == false){
        cout << "WSA error" << endl;
        return 0;
    }

    if(socket.CreateSocketAndAddr() == false){
        cout << "Create error" << endl;
    }

    if(socket.CreateSocketAndConnect() == 0){
        cout << "Connect error" << endl;
        return 0;
    }

    SOCKET serverSocket = socket.Getserversocket();

    while (true){
        SOCKET clientSocket;
        sockaddr_in client_sin;
        char msg[100];//存储传送的消息
        int len = sizeof(client_sin);
        cout<<"..."<<endl;
        clientSocket = accept(serverSocket, (sockaddr*)&client_sin, &len);
        if (clientSocket == INVALID_SOCKET){
            cout << "Accept error" << endl;
            return 1;
        }
        cout << "接收到一个链接：" << inet_ntoa(client_sin.sin_addr) << " (ip地址)" << endl;
        // system("pause");
        int num = recv(clientSocket, msg, 100, 0);
        string name = msg;
        if (num > 0){
            msg[num] = '\0';
            name = msg;
            clientsockets[name] = clientSocket;
            cout <<"客户端的名称为: "<< msg << endl;
        }else{
            closesocket(clientSocket);
            continue;
        }
        thread th = thread(RecAndSend, name, clientSocket);
        th.detach();
    }


    socket.CloseWSA();

    return 0;
}