 #include <windows.h> 
 #include <winsock.h>
 #include <string>
 #pragma comment(lib,"wsock32.lib")

// 获取本地网路IP
std::string CheckIP()
{
	WSADATA wsaData;
	char name[255];
	char* ip;
	PHOSTENT hostinfo;
	std::string ipStr;
    
    if(WSAStartup(MAKEWORD(2,0),&wsaData) == 0)
    {
        if(gethostname(name, sizeof(name)) == 0)
        {
            if((hostinfo = gethostbyname(name)) != NULL)
            {
                ip = inet_ntoa(*(struct in_addr*)*hostinfo->h_addr_list);
                ipStr = ip;
            }
        }
        WSACleanup();
    }
    return ipStr;
}
int main(int argc, char *argv[])
{
     printf("my IP is %s",CheckIP().c_str());
     system("pause");
     return 1;
}
