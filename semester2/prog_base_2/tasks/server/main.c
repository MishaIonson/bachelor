#include <stdio.h>
#include <stdlib.h>
#include <winsock.h>
#include "socket.h"
#include "server.h"
#include "driver.h"
#include "http.h"
#define BUFFER_SIZE 2000
static socket_t * winSock;
int main()
{
    fill_teach();
    int PORT = 5000;
    lib_init();
    winSock = socket_new();
    //CHECKING IF SOCKET IS FREE, CLOSING APP IF NOT
    if (socket_bind(winSock, PORT) == SOCKET_ERR)
    {
        printf("Cannot bind %i port\n", PORT);
        socket_close(winSock);
        socket_free(winSock);
        return 0;
    }
    socket_listen(winSock);
    char buffer[10000];
    socket_t * client = NULL;
    while(1)
    {
        printf("Waiting for connections\n");
        client = socket_accept(winSock);
        if (client == NULL)
        {
            printf("NULL pointer client\n");
            break;
        }
        int readStatus = socket_read(client, buffer, sizeof(buffer));
        if (readStatus <= 0)
        {
            printf("empty socket\n");
            socket_close(client);
            socket_free(client);
            continue;
        }
        printf(" Request recieved (readStatus: %i):\n'%s'\n", readStatus, buffer);

        http_request_t request = http_request_parse(buffer);

        if (strcmp(request.uri, "/") == 0)
        {
            server_homepage(client);
        }
        else if (strcmp(request.uri, "/drivers") == 0 || strcmp(request.uri, "/drivers/") == 0)
        {
            server_drivers(client, &request);
        }
        else if (strstr(request.uri, "/drivers/") != NULL)
        {
            char * string = strstr(request.uri, "/driver/");
            char * token = strtok(request.uri, "/");
            token = strtok(NULL, "/");
            if (token != NULL && isdigit(token[0]) != 0)
            {
                int index = atoi(token);
                int amount = driver_getSize();
                if (index >= 0)
                {
                    int i;
                    for (i = 0; i < amount; i++)
                    {
                        int get = driver_getId(i);
                        if (index == get)
                        {
                            server_driverId(client, &request, i);
                            break;
                        }
                    }
                    if(buffer[0]=='P')
                        server_driverId(client, &request, driver_getSize());

                }
            }
        }
        server_error(client);
    }

    socket_free(client);
    lib_free();
}
