/* server.h/server.c are analyzing the type of requests (GET/POST/DELETE),
the way the requests are sent (API (cJSON)/HTML)
and actually the path that requests are sent to.
For more information check out server.c file. */

#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED

#include "socket.h"
#include "http.h"
#include "database.h"

void server_analyzeRequest(http_request_t * request, socket_t * client, database_t * db);

void server_API_homepage(socket_t * client, char * message);
void server_API_alldrivers(database_t * db, socket_t * client, http_request_t * req);
void server_API_alldrivers_WHERE(database_t * db, socket_t * client, http_request_t * req, int moneyInv, condition moneyInvSign, int exp, condition expSign);
void server_API_driverByID(database_t * db, socket_t * client, http_request_t * req, int ID);

void server_HTML_homepage(socket_t * client, char * message);
void server_HTML_alldrivers(database_t * db, socket_t * client, http_request_t * req);
void server_HTML_newdriver(database_t * db, socket_t * client);
void server_HTML_driverByID(database_t * db, socket_t * client, http_request_t * req, int ID);

void server_invalidResponce(socket_t * client, char * message);

#endif //SERVER_H_INCLUDED
