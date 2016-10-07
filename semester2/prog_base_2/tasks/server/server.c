#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "http.h"
#include <ctype.h>
#include "driver.h"
#include "server.h"
driver drivers[4];
void fill_teach()
{
	int p = driver_fillArray(4,drivers);
}

int driver_getSize(void) {
    return (sizeof(drivers)/sizeof(drivers[0]));
}
int driver_getId(int i){
    int p = drivers[i].id;
    return drivers[i].id;
}
void server_homepage(socket_t * client)
{
    char homebuffer[10000];
    char * homePage = "he, type /drivers for list";
    sprintf(homebuffer,"HTTP/1.1 200 OK\n"
		"Content-Type: text/html\n"
		"Content-Length: %zu\n"
		"Connection: keep-alive\n"
		"\n%s",strlen(homePage),homePage);
		socket_write_string(client,homebuffer);
		socket_close(client);
}
void server_drivers(socket_t * client, http_request_t * req)
{
    char buffer[10240];
	if (strcmp(req->method, "GET") == 0) {

		int amount = driver_getSize();
		char * driversJSON = driver_parseAllToJSON(drivers, amount);
		sprintf(buffer,
			"HTTP/1.1 200 OK\n"
			"Content-Type: application/json\n"
			"Content-Length: %zu\n"
			"Connection: keep-alive\n"
			"\n%s", strlen(driversJSON), driversJSON);
		free(driversJSON);
	}
	else {
		char * errText = "Invalid command!";
		sprintf(buffer,
			"HTTP/1.1 404 \n"
			"Content-Type: text/html\n"
			"Content-Length: %zu\n"
			"\n%s", strlen(errText), errText);
	}
	socket_write_string(client, buffer);
	socket_close(client);
}
void server_driverId(socket_t * client, http_request_t * req, int index) {
	char strbuf[10000];
	if (strcmp(req->method, "GET") == 0) {
            int i;
            for(i=0;i<5;i++)
            {
                printStruct(&drivers[index]);
                printf("\n");
            }

		char * teachJSON = driver_parseToJSON(&drivers[index]);
		sprintf(strbuf,
			"HTTP/1.1 200 OK\n"
			"Content-Type: application/json\n"
			"Content-Length: %zu\n"
			"Connection: keep-alive\n"
			"\n%s", strlen(teachJSON), teachJSON);
		free(teachJSON);
	}
	else if (strcmp(req->method, "POST") == 0) {
		char * str = http_request_getArg(req, "name");
		if(str==NULL)
        {
             server_error(client);
             return;
        }

		if (str != NULL && strlen(str) < 25) {
            strcpy(drivers[index].firstName,str);
		}
		str = http_request_getArg(req, "group");
		if (str != NULL && strlen(str) < 25) {
			  strcpy(drivers[index].lastName,str);
		}
		str = http_request_getArg(req, "variant");
		if (str != NULL && isdigit(str[0]) != 0 && strlen(str) < 7) {
			drivers[index].id = atof(str);
		}


        printStruct(&drivers[index]);
		char * tJSON = driver_parseToJSON(&drivers[index]);
		printf("New student with id %i , type /drivers/%i to get full info", drivers[index].id,drivers[index].id , tJSON);
		sprintf(strbuf,
			"HTTP/1.1 200 OK\n"
			"Content-Type: application/json\n"
			"Content-Length: %zu\n"
			"Connection: keep-alive\n"
			"\n%s", strlen(tJSON), tJSON);
		free(tJSON);
	}
	else if (strcmp(req->method, "DELETE") == 0) {

         driver_init(&drivers[index]);
         int i;
         for(i=0;i<5;i++)
        {
            printStruct(&drivers[i]);
        }

		char * delTeachJSON = driver_parseToJSON(&drivers[index]);
		printf("Deleted student (%i-th one):\n%s\n", index, delTeachJSON);
		char * delText = "Student deleted successfully!";
		sprintf(strbuf,
			"HTTP/1.1 200 OK\n"
			"Content-Type: application/json\n"
			"Content-Length: %zu\n"
			"Connection: keep-alive\n"
			"\n%s", strlen(delText), delText);
		free(delTeachJSON);
	}
	else {
		char * errText = "Invalid command!";
		sprintf(strbuf,
			"HTTP/1.1 404 \n"
			"Content-Type: text/html\n"
			"Content-Length: %zu\n"
			"\n%s", strlen(errText), errText);
	}
	socket_write_string(client, strbuf);
	socket_close(client);
}
void server_error(socket_t * client) {
	char replyBuf[1000];
	char * errText = "ERROR";
	sprintf(replyBuf,
		"HTTP/1.1 404 \n"
		"Content-Type: text/html\n"
		"Content-Length: %zu\n"
		"\n%s", strlen(errText), errText);
	socket_write_string(client, replyBuf);
	socket_close(client);
}
