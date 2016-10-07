#include "PostOffice.h"
#include <stdlib.h>
#include <stdio.h>

struct Mail_s{
};

struct Mail_s* Mail_new()
{
    struct Mail_s* mail = malloc(sizeof(struct Mail_s));

    return mail;
}

void Mail_free(struct Mail_s* mail)
{
    free (mail);
}
