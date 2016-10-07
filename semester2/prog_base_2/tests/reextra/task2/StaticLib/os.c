#include "program.h"
#include "os.h"

struct program_s {
    char name[20];
    int memoryTakes;
    int isOpen;
};

struct os_s
{
    struct program_s *progs[MAX_THREADS];
	int ram;
    int ramUsing;
    int progsNumber;
    int memory;
	int memoryUsing;
};

struct os_s* os_new(int memorySize, int ramSize)
{
    struct os_s *osObject = malloc(sizeof(struct os_s));

    for (int i = 0; i < MAX_THREADS; i++)
        osObject->progs[i] = program_new("", 0);

    osObject->ramUsing = 0;
    osObject->progsNumber = 0;
    osObject->memoryUsing = 0;
    osObject->memory = memorySize;
	osObject->ram = ramSize;

    return osObject;
}

void os_installNewProgram(struct os_s* systemObj, char nameIn[20], int memoryTakesIn)
{
    if (systemObj->memoryUsing + memoryTakesIn > systemObj->memory)
        return;

    struct program_s* newProg = program_new(nameIn, memoryTakesIn);
    systemObj->progs[systemObj->progsNumber] = newProg;

    systemObj->progsNumber++;
    systemObj->memoryUsing += memoryTakesIn;
}

void os_deleteProg(struct os_s* systemObj, char *progName)
{
    int id = 0;

    while(strcmp(systemObj->progs[id]->name, progName) != 0)
    {
        id++;
        if (systemObj->progsNumber <= id)
            return;
    }
    systemObj->memoryUsing -= systemObj->progs[id]->memoryTakes;
    if (systemObj->progs[id]->isOpen == 1)
        systemObj->ramUsing -= systemObj->progs[id]->memoryTakes;

    for (int i = id; i < systemObj->progsNumber - 1; i++)
        systemObj->progs[i] = systemObj->progs[i + 1];

    systemObj->progsNumber--;
}

void os_openProg(struct os_s* systemObj, char progName[20])
{
    int id = 0;

    while(strcmp(systemObj->progs[id]->name, progName) != 0)
    {
        id++;
        if (systemObj->progsNumber <= id)
            return;
    }

    if (systemObj->ramUsing + systemObj->progs[id]->memoryTakes > systemObj->ram)
        return;
    else if (systemObj->progs[id]->isOpen == 1)
        return;
    else
    {
        systemObj->ramUsing += systemObj->progs[id]->memoryTakes;
        systemObj->progs[id]->isOpen = 1;
    }

}

void os_closeProg(struct os_s* systemObj, char *progName)
{
    int id = 0;

    while(strcmp(systemObj->progs[id]->name, progName) != 0)
    {
        id++;
        if (systemObj->progsNumber <= id)
            return;
    }

    if (systemObj->progs[id]->isOpen == 0)
        return;
    else if (systemObj->progs[id]->isOpen == 1)
    {
        systemObj->ramUsing -= systemObj->progs[id]->memoryTakes;
        systemObj->progs[id]->isOpen = 0;
    }
}

void os_getRam(struct os_s* obj)
{
    printf("\nRam: %i.   Using: %i\n", obj->ram, obj->ramUsing);
}

void os_getMemory(struct os_s* obj)
{
    printf("\nMemory: %i.   Using: %i\n", obj->memory, obj->memoryUsing);
}

void os_getListOpenedProgs(struct os_s* obj)
{
    int totalNum = 0;
    printf("LIST: \n");
    for (int i = 0; i < obj->progsNumber; i++)
    {
        if (obj->progs[i]->isOpen == 1)
        {
            printf("%s\n", obj->progs[i]->name);
            totalNum++;
        }

    }
    printf("TOTAL NUM: %i \n", totalNum);
}

void os_getListInstalledProgs(struct os_s* obj)
{
    printf("TOTAL NUMBER: %i\n", obj->progsNumber);
    for (int i = 0; i < obj->progsNumber; i++)
        printf("%s\n", obj->progs[i]->name);
}


void os_free(struct os_s* obj)
{
    for (int i = 0; i < obj->progsNumber; i++)
        program_free(obj->progs[i]);
    free(obj);
}
