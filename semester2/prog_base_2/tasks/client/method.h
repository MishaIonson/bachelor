#ifndef METHOD_H
#define METHOD_H
#define NO_FLAGS_SET 0
#define PORT 80
#define MAXBUFLEN 20480
#define LINE_SIZE 200

char *method_request(SOCKET recvSocket, const char request [], char buffer [], int maxLen);
char * method_secret(char * buffer_p);
void method_list(char * list, char * buffer_p);
void method_getSum(char * list, int size, char *sumLine);

#endif