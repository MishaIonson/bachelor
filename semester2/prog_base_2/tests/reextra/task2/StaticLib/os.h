#ifndef OS_H
#define OS_H

#include "program.h"
#define MAX_THREADS 1000

struct os_s* os_new(int memorySize, int ramSize);
void os_installNewProgram(struct os_s* systemObj, char* nameIn, int memoryTakesIn);
void os_deleteProg(struct os_s* systemObj, char *progName);
void os_openProg(struct os_s* systemObj, char *progName);
void os_closeProg(struct os_s* systemObj, char *progName);
void os_getRam(struct os_s* obj);
void os_getMemory(struct os_s* obj);
void os_getListOpenedProgs(struct os_s* obj);
void os_getListInstalledProgs(struct os_s* obj);
void os_free(struct os_s* obj);

#endif
