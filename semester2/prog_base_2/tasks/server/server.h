#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED
#include <winsock.h>
#include "socket.h"
#include "driver.h"
#include <string.h>
#include "http.h"
void server_homepage(socket_t * client);
int driver_getId(int i);
void fill_teach();
int driver_getSize(void);
void server_drivers(socket_t * client, http_request_t * req);
void server_driverId(socket_t * client, http_request_t * req, int index);
void server_error(socket_t * client);

#endif // SERVER_H_INCLUDED
