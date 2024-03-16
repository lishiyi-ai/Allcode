
#include <stdlib.h>
#include <stdio.h>
#include "Winsock2.h"
#pragma comment(lib, "ws2_32.lib")
#include "Windows.h"
 
 
int main(int argc, char *argv[])  
{  
	WSADATA wsaData;
	int nResult;
	nResult = WSAStartup(MAKEWORD(2,2), &wsaData);
	if (NO_ERROR != nResult)
	{
		return false; 
	}
 
	// 使用gethostname()函数，必须进行上面的初始化操作///  
	
	/* get the host name */  
	char hostname[MAX_PATH] = {0};
	scanf("%s",hostname);
	// gethostname(hostname,MAX_PATH); 
  
	hostent *host;
	if ((host = gethostbyname(hostname)) == NULL) {  
		perror("gethostbyname");  
		return(1);  
	} 
 
	printf("Host name is: %s\n", host->h_name);  
	printf("Host addrtype is: %d\n", host->h_addrtype);  
	printf("Host length is: %d\n", host->h_length);  
	
	/* printf ip address according to addrtype */  
	for(int i=0; host->h_addr_list[i]; i++)
		printf("IP addr %d: %s \n", i+1,
		inet_ntoa(*(struct in_addr*)host->h_addr_list[i])); 
	system("pause");
	return 0;  
}