#ifndef MSERVER_H
#define MSERVER_H
typedef enum server_status{
    SERVER_OK,
    OVERFLOW_CLIENTS,
    WRONG_ID,
    NO_CLIENT_WITH_THIS_ID
} server_status;


typedef struct mclient_s mclient_t;

typedef struct mserver_s mserver_t;
mserver_t *mserver_new(int idInput);

mclient_t *mserver_getClient(mserver_t *ms, int id);
int mserver_getClientsNumber(mserver_t *ms);
int mserver_getStatus(mserver_t *ms);
void mserver_newClient(mserver_t* ms);

void mserver_free(mserver_t *ms);
#endif

