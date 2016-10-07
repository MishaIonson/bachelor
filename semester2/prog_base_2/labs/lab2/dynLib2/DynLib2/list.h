#include <stdlib.h>
#include <stdio.h>
typedef struct list_s list_t;
struct list_s{
    char line[10];
    int length;
};
void list_Spaces(struct list_s* list);
