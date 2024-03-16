#include<winsock2.h>
#include<iostream>
#include<string>
#include<thread>
using namespace std;
#pragma comment(lib, "ws2_32.lib")

bool CreateSocketAndConnect(SOCKET clientSocket);
void getnameAndinfo(char msg[], int num, string &name, string &msg1);
void rev(SOCKET soekct);
void sed(SOCKET socket);


bool ManyConnectServer(SOCKET clientSocket){
    int i = 16;
    while(i--){
        if(CreateSocketAndConnect(clientSocket) == 1){
            cout<<"连接成功"<<endl;
            
            // 获取用户名
            cout << "输入用户名:" <<endl;
            string text;
            getline(cin, text);
            const char * msg;
            msg = text.c_str();
            send(clientSocket, msg, strlen(msg), 0);
            break;
        }else{
            cout<<"等待重试连接"<<endl;
            Sleep(10000);
        }
    }
    if(i == -1){
        cout<<"连接失败"<<endl;
        return 0;
    }
    return 1;
}

// 连接服务器
bool CreateSocketAndConnect(SOCKET clientSocket){
    int i = 30;
    while(i--){
        if (clientSocket == INVALID_SOCKET){
            cout << "Socket error" << endl;
            return 0;
        }
        sockaddr_in sock_in;
        sock_in.sin_family = AF_INET;
        sock_in.sin_port = htons(8080);
        sock_in.sin_addr.S_un.S_addr = inet_addr("192.168.199.67");
        if (connect(clientSocket, (sockaddr*)&sock_in, sizeof(sock_in) )== SOCKET_ERROR){
            cout << "Connect error" << endl;
            Sleep(100);
            // return 0;
        }else{
            break;
        }
    }
    if (i == -1){
        return 0;
    }
    return 1;
}

// 得到发信者和信息
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

// 接收消息
void rev(SOCKET socket){
    while(true){
        char msg[1024];
        int num = recv(socket, msg, 1024, 0);
        // 发送的为空报文表示该服务器已经关闭
        if(num <= 0){
            cout << "服务器关闭或出现错误" << endl;
            return;
        }
        string name;
        string msg1;
        msg[num] = '\0';
        getnameAndinfo(msg, num, name, msg1);
        cout << "[" << name << "]: "<< msg1 << endl;

    }
}

// 发送消息
void sed(SOCKET socket){
    // 获取好友名
    string name;
    cout<<"输入你好友的名字:"<<endl;
    getline(cin, name);
    while(true){
        cout<<"输入发送的信息:"<<endl;
        string text;
        getline(cin, text);
        const char * msg;
        string all = name + " " + text;
        // cout<< all << endl;
        msg = all.c_str();
        int iret =send(socket, msg, strlen(msg), 0);
        // cout<<"发送完成"<<endl;
        if(iret == SOCKET_ERROR){
            cout<<"无法连接到服务器"<<endl;
            break;
        }
        // cout<<"下一轮"<<endl;
    }
    cout << "退出发送线程" << endl ;
    system("pause");
}



int main(int argc, char* argv[])
{

    // 初始化DLL
    // MAKEWORD是把第一个参数和第二个参数的八位二进制数拼接起来
    // socket编程中：   
    // 声明调用不同的Winsock版本。例如MAKEWORD(2,2)就是调用2.2版，MAKEWORD(1,1)就是调用1.1版。
    WORD sockVersion = MAKEWORD(2, 2);
    WSADATA data;
    if (WSAStartup(sockVersion, &data) != 0){
        return 1;
    }

    // 创建代理客户端
    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    // 多次重试连接服务器;
    while(true){
        if(ManyConnectServer(clientSocket) == 1){
            // 创建接收进程和发送进程
            thread rec = thread(rev, clientSocket);
            thread sd = thread(sed, clientSocket);
            rec.join();
            sd.join();
        }else{
            cout << "请稍后进行重试" << endl;
            break;
        }
        cout<<"准备重新建立连接";
    }


    // 关闭客户端
    closesocket(clientSocket);
    WSACleanup();

    return 0;
}