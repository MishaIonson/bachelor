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
mserver_t *mserver_new(int idInput)
{
    mserver_t *ms = malloc(sizeof(struct mserver_s));
    ms->id = idInput;
    ms->clientsNumber=0;
    ms->status = SERVER_OK;

    if ((idInput<0) || (idInput > 1711))
    {
        ms->status = WRONG_ID;
    }
}

mclient_t *mserver_getClient(mserver_t *ms, int id)
{
    if (ms->clientsNumber<=id)
    {
        ms->status = NO_CLIENT_WITH_THIS_ID;
        return;
    }
    return ms->clients[id];
}

int mserver_getClientsNumber(mserver_t *ms)
{

	return ms->clientsNumber;
}

int mserver_getStatus(mserver_t *ms)
{
    return ms->status;
}

void mserver_newClient(mserver_t* ms)
{
    if (ms->clientsNumber+1 >= 10)
    {
        ms->status = OVERFLOW_CLIENTS;
        return;
    }

    mclient_t* mc = malloc(sizeof(struct mclient_s));
    mc->serverId = ms->id;
    mc->id = mserver_getClientsNumber(ms);
    mc->messagesNumber = 0;
    mc->status = CLIENT_OK;
    ms->clients[mc->id] = mc;
    ms->clientsNumber++;

}

void mserver_free(mserver_t *ms)
{
    free(ms);
}
