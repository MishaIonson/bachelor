#include <winsock2.h>
#include <windows.h>
#include <strings.h>

#include "method.h"

#pragma comment(lib, "ws2_32.lib")


int main(){
    WSADATA Data;
    SOCKADDR_IN recvSockAddr;
    SOCKET recvSocket;
    int status;
    int numrcv = 0;
    struct hostent * remoteHost;
    char * ip;
    const char * host_name = "pb-homework.appspot.com";
    char buffer[10000];

    memset(buffer,0,10000);
    status = WSAStartup(MAKEWORD(2, 2), &Data);

    if(status != 0)
    {
        printf("ERROR: WSAStartup unsuccessful\r\n");
        return 0;
    }

	remoteHost = gethostbyname(host_name);
	ip = inet_ntoa(*(struct in_addr *)*remoteHost->h_addr_list);
	printf("IP address is: %s.\n", ip);
    memset(&recvSockAddr, 0, sizeof(recvSockAddr));
    recvSockAddr.sin_port=htons(PORT);
    recvSockAddr.sin_family=AF_INET;
    recvSockAddr.sin_addr.s_addr= inet_addr(ip);
	recvSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if(recvSocket == INVALID_SOCKET)
	{
		printf("ERROR: socket unsuccessful\r\n");
             WSACleanup();
		system("pause");
		return 0;
	}

    if(connect(recvSocket,(SOCKADDR*)&recvSockAddr,sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
    {
        printf("ERROR: socket could not connect\r\n");
        closesocket(recvSocket);
        WSACleanup();
        return 0;
    }

    char request[LINE_SIZE];
    sprintf(request, "GET /var/9 HTTP/1.1\r\nHost:%s\r\n\r\n", host_name);

    char * buffer_p = method_request(recvSocket, request, buffer, 10000);

    char * p = method_secret(buffer_p);

    sprintf(request, "GET /var/9?secret=%s HTTP/1.1\r\nHost:%s\r\n\r\n", p, host_name);
    buffer_p = method_request(recvSocket, request, buffer, 10000);

    char list[strlen(buffer_p)];
    method_list(list, buffer_p);

    char sumLine[strlen(buffer_p)];

    method_getSum(list, strlen(buffer_p), sumLine);


    char result[strlen(buffer_p)];
    sprintf(result, "result=%s", sumLine);
    printf("%s\n\n", result);

    sprintf(request, "POST %s/var/9 HTTP/1.1\r\n"
            "Content-length: %d\r\n\r\n"
            "%s", host_name, strlen(result), result);
    method_request(recvSocket, request, buffer, 10000);
    return 0;
}
