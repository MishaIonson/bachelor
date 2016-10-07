#ifndef PROGRAM_H
#define PROGRAM_H


struct program_s* program_new(char* nameIn, int memoryTakesIn);
void program_free(struct program_s* obj);

#endif

