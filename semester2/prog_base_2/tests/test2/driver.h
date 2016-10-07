#ifndef TEACHER_H_INCLUDED
#define TEACHER_H_INCLUDED
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

struct bus
{
    char  busName[100];
    int id;
};

typedef struct driver
{
    char  firstName[100];
    char  lastName[100];
    float salary;
    struct tm birthday;
    int id;
    struct bus driver_bus;
} driver;
void printStruct(driver * driver);
int driver_fillArray(size_t size,driver drivers[size]);
void teacher_init(driver *d);
#endif // TEACHER_H_INCLUDED
