#include <winsock2.h>
#include <windows.h>
#include "method.h"
#define MAXBUFLEN 20480
#define NO_FLAGS_SET 0

char *method_request(SOCKET recvSocket, const char request [], char buffer [], int maxLen){
    send(recvSocket, request, strlen(request), 0);

    int numrcv = 0;
    int status = 0;
    int i;
    for (i=0; i<MAXBUFLEN; i++){
        buffer[i] = 0;
    }

    numrcv = recv(recvSocket, buffer, MAXBUFLEN, NO_FLAGS_SET);
    if (numrcv == SOCKET_ERROR)
    {
        printf("ERROR: recvfrom unsuccessful\r\n");
        status = closesocket(recvSocket);
        if(status == SOCKET_ERROR)
			printf("ERROR: closesocket unsuccessful\r\n");
        status = WSACleanup();
        if (status == SOCKET_ERROR)
			printf("ERROR: WSACleanup unsuccessful\r\n");
        system("pause");
        return(1);
    }

    printf("%s\r\n", buffer);

    return buffer;
}

char * method_secret(char * buffer_p){
    char *p;
    char delete[] = "=";
    p = strtok(buffer_p, delete);
    p = strtok(NULL, delete);
    p = strtok(NULL, delete);

    printf("\nSecret word is '%s'\n\n", p);
    return p;
}

void method_list(char * list, char * buffer_p){
    int i = 0;
    int j = 0;
    while (j<6){ //6 - an amount of strings of information about server
        if (buffer_p[i++]=='\n'){
            j++;
        }
    }

    strcpy(list, buffer_p+i);
    return;
}

void method_getSum(char * list, int size, char *sumLine){
    int element;
	int sum = 0;
    char str[size];
    char delete[] = " ";
    char * p = strtok(list, delete);
    while(p!=NULL){
        strcpy(str, p);
        p = strtok(NULL, delete);
        element = atoi(p);
        if (element > 0)
		{
			sum+=element;
            strcpy(sumLine, str);
        }
    }
	sprintf(sumLine, "%i", sum);
	return;
}
