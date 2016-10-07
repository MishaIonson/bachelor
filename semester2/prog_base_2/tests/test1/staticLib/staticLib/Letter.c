#include "Letter.h"
#include <stdlib.h>
#include <stdio.h>

struct Letter_s{
    int wasOpened; // TRUE, FALSE
    char author[10];
    char theme[10];
    char body[100];
    int answers;
    int adressID;
    char recipient[10];
    void (*user_callback)();
};

struct Letter_s* Letter_new()
{
    struct Letter_s* letter = malloc(sizeof(struct Letter_s));
    letter->wasOpened = 1;
    letter->answers = 0;

    return letter;
}

void Letter_free(struct Letter_s* letter)
{
    free(letter);
}

void Letter_getInfo(struct Letter_s* letter)
{
    printf("Letter to: %s\n", letter->recipient);
    printf("From: %s\n", letter->author);
    printf("%s", letter->body);
    printf("%i", letter->answers);
}

