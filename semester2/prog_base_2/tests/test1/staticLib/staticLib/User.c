#include "User.h"
#include <stdlib.h>
#include <stdio.h>

struct User_s{
    char name[10];
};

struct User_s* User_new()
{
    struct User_s* user = malloc(sizeof(struct User_s));

    return user;
}

void User_free(struct User_s* user)
{
    free(user);
}

