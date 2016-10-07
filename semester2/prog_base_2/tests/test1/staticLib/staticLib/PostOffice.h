#ifndef POSTOFFICE_H_INCLUDED
#define POSTOFFICE_H_INCLUDED

typedef struct PostOffice_s PostOffice_t;

enum { OK, LIST_FORMED,
};

struct PostOffice_s* PostOffice_new();

void PostOffice_free(struct PostOffice_s* postOffice);
struct List_s* PostOffice_getLetterList(struct PostOffice_s* postOffice);
// void PostOffice_sendAnswer(struct PostOffice_s* postOffice, struct Letter_s* letterIn, char text[100], int andressIdentificator);
void PostOffice_sendLetter(struct PostOffice_s* postOffice, char letterInput[100], int andressIdentificator);
int PostOffice_getUnreadedLetterNumber(struct PostOffice_s* postOffice);
struct List_s* PostOffice_getUnreadedLetterList(struct PostOffice_s* postOffice);
struct List_s* PostOffice_getReadedLetterList(struct PostOffice_s* postOffice);
struct List_s* PostOffice_getLetterList(struct PostOffice_s* postOffice);

#endif
