#include <stdlib.h>
#include <stdio.h>
#include "list.h"

struct list_s* list_new()
{
    struct list_s *list = malloc(sizeof(struct list_s));
    return list;
}

void list_free(struct list_s *list)
{
    free(list);
}

void list_fillLine(struct list_s* list)
{
    printf("enter 10 characters: ");
    if (list->posFilled < 9)
    {
        fgets(list->line, 10, stdin);
        list->posFilled = 9;
    }

}

void list_start(struct list_s* list)
{
    list->length = 10;
    list->posFilled = -1;
    list_fillLine(list);
}

void list_print(struct list_s* list)
{
    printf("\nLine: ");
    int i;
    for (i=0;  i< list->length; i++)
        printf("%c", list->line[i]);
    printf("\n");
}
