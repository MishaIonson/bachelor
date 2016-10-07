#include <stdio.h>
#include <stdlib.h>
#include "windows.h"
struct list_s* list_new();
void list_free(struct list_s *list);
void list_fillLine(struct list_s* list);
void list_start(struct list_s* list);
void list_print(struct list_s* list);

typedef void (*SomeFunction)(const LPCSTR sometext);

void forDLL1Testing(struct list_s* list)
{

    SomeFunction someFunc = NULL;
    HINSTANCE hLib = LoadLibrary("DynLib.dll");

    someFunc = (SomeFunction)GetProcAddress(hLib, "SomeFunction");

    SomeFunction vowelsFunc = NULL;
    vowelsFunc = (SomeFunction)GetProcAddress(hLib, "list_vowelChecking");
    vowelsFunc(list);

    FreeLibrary(hLib);
}

void forDLL2Testing(struct list_s* list)
{

    SomeFunction someFunc = NULL;
    HINSTANCE hLib = LoadLibrary("DynLib2.dll");

    someFunc = (SomeFunction)GetProcAddress(hLib, "SomeFunction");

    SomeFunction spacesFunc = NULL;
    spacesFunc = (SomeFunction)GetProcAddress(hLib, "list_Spaces");
    spacesFunc(list);

    FreeLibrary(hLib);
}

int main()
{
    // part 1

    struct list_s *list;
    list = list_new();
    list_start(list);

    list_print(list);

    // part 2

    forDLL1Testing(list);//  dll1




    forDLL2Testing(list);//  dll2
    list_print(list);

    return 0;
}
