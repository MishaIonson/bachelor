#include "program.h"

struct program_s {
    char name[20];
    int memoryTakes;
    int isOpen;
};


struct program_s* program_new(char nameIn[20], int memoryTakesIn)
{
    struct program_s *prog = malloc(sizeof(struct program_s));

    strcpy(prog->name, nameIn);
    prog->memoryTakes = memoryTakesIn;
    prog->isOpen = 0;

    return prog;
}


void program_free(struct program_s* obj)
{
    free(obj);
}
