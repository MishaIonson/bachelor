#ifndef MAIL_H_INCLUDED
#define MAIL_H_INCLUDED

typedef struct Mail_s Mail_t;

struct Mail_s* Mail_new();

void Mail_free(struct Mail_s* mail);


#endif
