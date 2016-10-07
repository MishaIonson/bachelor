#include "mserver.h"
#include "mclient.h"

struct mclient_s{
	int id;
	int serverId;
	int connectedServerId;
	int messages[10];
	int messagesNumber;
	int messageClientId;
	client_status *status;
};

struct mserver_s{
	int id;
	int clientsNumber;
	mclient_t *clients[100];
	server_status *status;
};

int mclient_getStatus(mclient_t *mc)
{
    return mc->status;
}
void mclient_sendMessage(mserver_t *ms, mclient_t *mc, int message, int clientIdTo)
{
    if ((ms->clientsNumber < mc->id) || (ms->clientsNumber < clientIdTo) || (mc->id == clientIdTo))
    {
        mc->status = WRONG_ADDRESS;
        return;
    }

    if ((message < 0 ) || (message > 87))
    {
        mc->status = WRONG_MESSAGE;
        return;
    }
    ms->clients[clientIdTo]->messages[ms->clients[clientIdTo]->messagesNumber] =message;
    ms->clients[clientIdTo]->messagesNumber++;
}

void mclient_free(mclient_t *mc)
{
    free(mc);
}
int mclient_getClientId(mclient_t *mc)
{
    return mc->id;
}
