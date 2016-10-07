#include "communicator.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct Communicator_s
{
    char identifier[10];
    char* messageIn;
     void (*messageCameIn) (Communicator_t* com, Communicator_t* c2, char message[]);
    status_t STATUS;
};

struct Communicator_s* communicator_new(char* ID)
{
    struct Communicator_s* com = malloc(sizeof(struct Communicator_s));
    com->STATUS = 0;
    strcpy(com->identifier, ID);
    if (!(((int)ID[0]>=(int)'0') && ((int)ID[0]<=(int)'9')))
        com->STATUS = WRONG_ID;
    return com;
}

struct Communicator_s* communicator_newD(char ID[], void (*callback) (Communicator_t* com, Communicator_t* c2, char message[]))
{
    struct Communicator_s* com = malloc(sizeof(struct Communicator_s));
    com->messageCameIn = callback;
    com->STATUS = OK;
    strcpy(com->identifier, ID);
    if (!(((int)ID[0]>=48) && ((int)ID[0]<=57)))
        com->STATUS = WRONG_ID;
    return com;
}
status_t getStatus(Communicator_t* c)
{
    return c->STATUS;
}
void communicator_free(Communicator_t* c)
{
    free(c);
}

char* communicator_getMessage(Communicator_t* c)
{
    return c->messageIn;
}

void communicator_sender(Communicator_t* com)
{
    printf(" .from %sst communicator. ", com->identifier);
}

void communicator_alternative(Communicator_t* com)
{
    printf("\n .alternative %sst communicator maker. \n", com->identifier);
}

void communicator_sendMessage(Communicator_t* sender, Communicator_t *to, char* message)
{
    printf("\n .came to %s communicator. \n", to->identifier);
    communicator_sender(sender);
}

void communicator_sendMessage_alternative(Communicator_t* sender, Communicator_t *to, char* message)
{
    printf("\n alternative function test .%s communicator. \n", to->identifier);
    communicator_sender(sender);
}

void comm_sendTo(Communicator_t* sender, Communicator_t *to[10], int toCount, char whom[2], char* message)
{
    int k = 0;
    if (toCount < 0)
    {
        sender->STATUS = WRONG_INDEXNUMBER;
        return;
    }
    int i = 0;
    while(i < toCount)
    {

        if ((NULL != to[i]) && (NULL != to[i]->messageCameIn))
            to[i]->messageCameIn(sender, to[i], message);
        i++;
    }

}

