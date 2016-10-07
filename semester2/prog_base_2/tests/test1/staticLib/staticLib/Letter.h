#ifndef LETTER_H_INCLUDED
#define LETTER_H_INCLUDED

typedef struct Letter_s Letter_t;

struct Letter_s* Letter_new();

void Letter_free(struct Letter_s* letter);


#endif


