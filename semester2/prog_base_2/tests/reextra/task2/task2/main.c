// VARIANT 11

#include <stdio.h>
#include <stdlib.h>
#include "os.h"
#include "program.h"


int main()
{
    struct os_s *systemObj;
    systemObj = systemObj = os_new(100, 10);

    // install test
    printf("//install test\n");
    os_installNewProgram(systemObj, "Kaspersky", 7);
    os_installNewProgram(systemObj, "Code::Blocks", 1);
    os_installNewProgram(systemObj, "Dota2", 12);

    os_getListInstalledProgs(systemObj);
    printf("\n");
    //

    // trying to install too huge program
    printf("//trying to install too huge program\n");
    os_installNewProgram(systemObj, "Witcher3", 100);

    os_getListInstalledProgs(systemObj);
    printf("\n");
    //

    // opening test
    printf("//opening test\n");
    os_openProg(systemObj, "Kaspersky");
    os_openProg(systemObj, "Code::Blocks");
    os_getListOpenedProgs(systemObj);
    printf("\n");
    //

    //trying to open too huge
    printf("//trying to open too huge\n");
    os_openProg(systemObj, "Dota2");
    os_getListOpenedProgs(systemObj);
    printf("\n");
    //

    //closing test
    printf("//closing test\n");
    os_closeProg(systemObj, "Kaspersky");
    os_getListOpenedProgs(systemObj);
    printf("\n");
    //

    // deleting test
    printf("//deleting test\n");
    os_deleteProg(systemObj, "Dota2");
    os_getListInstalledProgs(systemObj);
    printf("\n");
    //


    //os_getListOpenedProgs(systemObj);
    //os_getMemory(systemObj);
    //os_getRam(systemObj);
    return 0;
}
