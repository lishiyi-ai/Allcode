#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

int main() {
    // 初始化WinSock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Failed to initialize WinSock." << std::endl;
        return 1;
    }

    // IP地址字符串
    const char* ip_address = "127.0.0.1";

    // 创建addrinfo结构体
    struct addrinfo hints, *result, *p;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC; // IPv4 或 IPv6
    hints.ai_socktype = SOCK_STREAM; // 流式套接字

    // 获取地址信息
    int status = getaddrinfo(ip_address, NULL, &hints, &result);
    if (status != 0) {
        std::cerr << "getaddrinfo error: " << gai_strerror(status) << std::endl;
        WSACleanup();
        return 1;
    }

    // 遍历获取到的地址信息
    for (p = result; p != NULL; p = p->ai_next) {
        // 获取对应的主机名
        char host[NI_MAXHOST];
        status = getnameinfo(p->ai_addr, p->ai_addrlen, host, sizeof(host), NULL, 0, NI_NAMEREQD);
        if (status != 0) {
            std::cerr << "getnameinfo error: " << gai_strerror(status) << std::endl;
            continue;
        }

        // 输出主机名
        std::cout << "IP Address: " << ip_address << " Hostname: " << host << std::endl;
    }

    // 释放获取到的地址信息
    freeaddrinfo(result);

    // 清理WinSock
    WSACleanup();
    system("pause");
    return 0;
}