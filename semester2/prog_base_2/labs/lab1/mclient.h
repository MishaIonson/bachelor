#ifndef MCLIENT_H
#define MCLIENT_H

#include "mserver.h"
// let's take the rule - messages can be the int numbers from 0 to 97
typedef enum client_status{
    CLIENT_OK,
    PZDC,
    OVERFLOW_MESSAGE_DATA,
    OVERFLOW_MESSAGES,
    WRONG_ADDRESS,
    WRONG_MESSAGE
}client_status;
typedef struct mclient_s mclient_t;


int mclient_getStatus(mclient_t *mc);
void mclient_sendMessage(mserver_t *ms, mclient_t *mc, int message, int clientIdTo);
void mclient_free(mclient_t *mc);

int mclient_getClientId(mclient_t *mc);
#endif
