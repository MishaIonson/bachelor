#include <stdlib.h>
#include <stdio.h>
typedef struct list_s list_t;
struct list_s{
    char line[10];
    int length;
    int posFilled;
};

struct list_s* list_new();

void list_free(struct list_s *list);

void list_fillLine(struct list_s* list);
void list_start(struct list_s* list);
void list_print(struct list_s* list);
