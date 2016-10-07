#include <stdio.h>
#include <stdlib.h>  // !
#include <stdarg.h>  // !
#include <stddef.h>  // !
#include <setjmp.h>  // !

#include <cmocka.h>

struct PostOffice_s* PostOffice_new();
void Letter_getInfo(struct Letter_s* letter);
typedef struct list_s list_t;
void PostOffice_sendAnswer(struct PostOffice_s* postOffice, struct Letter_s* letterIn, char text[100], int andressIdentificator);
void * list_get(list_t * self, int index);
struct Letter_s* Letter_new();
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



static void makeAnswer_goodInput(void **state)
{
    struct PostOffice_s* po = PostOffice_new();
    struct Letter_s* letter2 = Letter_new();
    letter2->authorID = 0;
    strcpy(letter2->author, "Rosberg");
    strcpy(letter2->body, "Hi! Win one more race");
    letter2->wasOpened = 1;

    PostOffice_sendAnswer(po, letter2, "text", 0);
    assert_int_equal(po->STATUS, 1);
}

int main(void) {
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(makeAnswer_goodInput),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
