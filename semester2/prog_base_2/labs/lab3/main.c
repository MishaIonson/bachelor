#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "communicator.h"
void unit_test_idTest1()
{
    Communicator_t* communicatorSender;

    communicatorSender = communicator_new("a");

    if (getStatus(communicatorSender) == OK)
        printf("\nTEST idTest1: FALSE");
    else if (getStatus(communicatorSender) == WRONG_ID)
        printf("\nTEST idTest1: TRUE");
}
void unit_test_idTest2()
{
    Communicator_t* communicatorSender;

    communicatorSender = communicator_new("1");

    if (getStatus(communicatorSender) == OK)
        printf("\nTEST idTest2: TRUE");
    else if (getStatus(communicatorSender) == WRONG_ID)
        printf("\nTEST idTest2: FALSE");
}
void unit_test_putWrongIndex()
{
    Communicator_t* communicatorSender;

    communicatorSender = communicator_new("1");

    struct Communicator_s* c[4];
    int i;
    char id[10] = "";
    for (i = 0; i < 10; i++)
        id[i]= '\0';
    //void (*messageCameIn) (Communicator_t* com, Communicator_t* c2, char message[]) = communicator_sendMessage;
     void (*messageCameIn) (Communicator_t* com, Communicator_t* c2, char message[]) =communicator_sendMessage_alternative;

    for (i = 0; i < 4; i++)
    {
        id[0] = i + '0';
        c[i] = communicator_newD(id, messageCameIn);
    }


    comm_sendTo(communicatorSender, c, -1, "hello");

    free(communicatorSender);
    for (i = 0; i < 4; i++)
        free(c[i]);


    if (getStatus(communicatorSender) == OK)
        printf("\nTEST WRONG_INDEX: FALSE");
    else if (getStatus(communicatorSender) == WRONG_INDEXNUMBER)
        printf("\nTEST WRONG_INDEX: TRUE");
}


int main()
{

    Communicator_t* communicatorSender;

    communicatorSender = communicator_new("1");

    struct Communicator_s* c[4];
    int i;
    char id[10] = "";
    for (i = 0; i < 10; i++)
        id[i]= '\0';
    //void (*messageCameIn) (Communicator_t* com, Communicator_t* c2, char message[]) = communicator_sendMessage;
     void (*messageCameIn) (Communicator_t* com, Communicator_t* c2, char message[]) =communicator_sendMessage_alternative;

    for (i = 0; i < 4; i++)
    {
        id[0] = i + '0';
        c[i] = communicator_newD(id, messageCameIn);
    }

    char mWhom[2];
    mWhom[0] = '0';
    mWhom[2] = '2';
    comm_sendTo(communicatorSender, c, 2, mWhom, "hello");

    free(communicatorSender);
    for (i = 0; i < 4; i++)
        free(c[i]);



    // TESTS:
    printf("\n\nTESTS: \n");
    unit_test_idTest1();
    unit_test_idTest2();
    unit_test_putWrongIndex();
    //unit_test_wrongAddress();

    return 0;
}
