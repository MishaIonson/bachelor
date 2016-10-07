#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED

typedef struct User_s User_t;

struct User_s* User_new();

void User_free(struct User_s* user);


#endif

