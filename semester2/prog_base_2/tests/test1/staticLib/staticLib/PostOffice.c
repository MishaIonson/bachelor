#include "PostOffice.h"
#include <stdlib.h>
#include <stdio.h>
#include "list.h"
//
#include "User.h"
#include "Mail.h"
#include "Letter.h"
//

struct PostOffice_s{
    struct User_s* user;
    struct Letter_s* letter;
    struct Mail_s* mail;
    struct list_s* letter_list;
    struct list_s* dialog_list;
    int STATUS;

};
struct Letter_s{
    int wasOpened; // TRUE, FALSE
    char author[10];
    int authorID;
    char theme[10];
    char body[100];
    int answers;
    int adressID;
    char recipient[10];
};
/*
typedef struct node_s node_t;
struct node_s {
    node_t * next;
    node_t * prev;
    void * data;
};
struct list_s {
    node_t * head;
    node_t * tail;
    int size;
    list_dealloc_fn deallocator;
};*/

struct PostOffice_s* PostOffice_new()
{
    struct PostOffice_s* postOffice = malloc(sizeof(struct PostOffice_s));

    postOffice->letter_list = list_new();
    postOffice->STATUS = 0;

    postOffice->dialog_list = list_new();

    return postOffice;
}

void PostOffice_free(struct PostOffice_s* postOffice)
{
    free(postOffice);
}

struct List_s* PostOffice_getLetterList(struct PostOffice_s* postOffice)
{
    return postOffice->letter_list;
}

struct List_s* PostOffice_getReadedLetterList(struct PostOffice_s* postOffice)
{
    struct list_s* list = list_new();

    int i;
    for (i = 0; i < list_getSize(postOffice->letter_list); i++)
    {
        struct Letter_s* letter = list_get(postOffice->letter_list, i);
        if (letter->wasOpened == 0)
            list_push_back(list, letter);
    }

    return list;
}

struct List_s* PostOffice_getUnreadedLetterList(struct PostOffice_s* postOffice)
{
    struct list_s* list = list_new();

    int i;
    for (i = 0; i < list_getSize(postOffice->letter_list); i++)
    {
        struct Letter_s* letter = list_get(postOffice->letter_list, i);
        if (letter->wasOpened == 0)
            list_push_back(list, letter);
    }

    return list;
}

int PostOffice_getUnreadedLetterNumber(struct PostOffice_s* postOffice)
{
    int answer = 0;

    int i;
    for (i = 0; i < list_getSize(postOffice->letter_list); i++)
    {
        struct Letter_s* letter = list_get(postOffice->letter_list, i);
        if (letter->wasOpened == 0)
            answer++;
    }

    return answer;
}

void PostOffice_sendLetter(struct PostOffice_s* postOffice, char letterInput[100], int andressIdentificator)
{
    struct Letter_s* letter = Letter_new();
    strcpy(letter->body, letterInput);
    letter->adressID = andressIdentificator;
    letter->answers = 0;
    strcpy(letter->theme, letterInput[0]);
    list_push_back(postOffice->letter_list, letter);
}

void PostOffice_sendAnswer(struct PostOffice_s* postOffice, struct Letter_s* letterIn, char text[100], int andressIdentificator)
{
    letterIn->answers+=1;
    struct Letter_s* letter = Letter_new();
    strcpy(letter->body, text);
    letter->adressID = andressIdentificator;
    letter->answers = 0;
    list_push_back(postOffice->letter_list, letter);

    postOffice->STATUS = 1;
    struct list_s* dialog = list_new();
    list_push_back(dialog, letter);
    list_push_back(dialog, letterIn);

    list_push_back(postOffice->dialog_list, dialog);

}


