#ifndef COM_H
#define COM_H

typedef struct Communicator_s Communicator_t;

typedef enum status_t{
    OK,
    WRONG_ID,
    WRONG_INDEXNUMBER,
    WRONG_ADDRESS
} status_t;
void communicator_free(Communicator_t* c);
status_t getStatus(Communicator_t* c);
char* communicator_getMessage(Communicator_t* c);
void communicator_sender(Communicator_t* com);
void communicator_sendMessage(Communicator_t* sender, Communicator_t *to, char* message);
void communicator_sendMessage_alternative(Communicator_t* sender, Communicator_t *to, char* message);

#endif // COM_H
