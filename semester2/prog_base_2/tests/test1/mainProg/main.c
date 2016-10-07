#include <stdio.h>
#include <stdlib.h>

struct PostOffice_s* PostOffice_new();
void Letter_getInfo(struct Letter_s* letter);
typedef struct list_s list_t;
void * list_get(list_t * self, int index);
void PostOffice_sendLetter(struct PostOffice_s* postOffice, char letterInput[100], int andressIdentificator);

struct PostOffice_s{
    struct User_s* user;
    struct Letter_s* letter;
    struct Mail_s* mail;
    struct list_s* letter_list;
    struct list_s* dialog_list;

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

int main()
{
    struct PostOffice_s* postOffice = PostOffice_new();
    struct Letter_s* letter1 = Letter_new();
    strcpy(letter1->author, "Vettel");
    letter1->authorID = 0;
    strcpy(letter1->body, "Hello, dude! Be better");
    letter1->wasOpened = 1;

    list_push_back(postOffice->letter_list, letter1);

    // 2
    struct Letter_s* letter2 = Letter_new();
    letter2->authorID = 0;
    strcpy(letter2->author, "Rosberg");
    strcpy(letter1->body, "Hi! Win one more race");
    letter2->wasOpened = 1;

    list_push_back(postOffice->letter_list, letter2);
    // 3
    struct Letter_s* letter3 = Letter_new();
    letter2->authorID = 0;
    strcpy(letter3->author, "Riccardo");
    strcpy(letter1->body, "-");
    letter3->wasOpened = 1;

    list_push_back(postOffice->letter_list, letter3);

    Letter_getInfo(letter3);
}
