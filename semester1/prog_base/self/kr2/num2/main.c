#include <stdio.h>
#include <stdlib.h>
struct man
{
    char name[100];
    char country[40];
};
struct startap
{
    char name[100];
    char theme[100];
    struct man *Man;
};
void makeZeroMan(struct startap *Man)
{
    strcpy(Man->name, ' ');
    strcpy(Man->country, ' ');
}
void makeZero(struct startap *s)
{
    strcpy(s->name, ' ');
    strcpy(s->theme, ' ');
    makeZeroMan(s->Man);
}
int main()
{
    struct startap s;
    makeZero(&s);
    printf("Hello world!\n");
    return 0;
}
