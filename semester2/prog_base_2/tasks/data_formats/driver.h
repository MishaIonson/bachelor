#include <time.h>

typedef struct bus_s{
	int ID;
	int Speed;
} bus_t;
typedef struct driver_s{
    char name[20];
    char surname[20];
    struct tm birthday;
    float salary;
    struct bus_s bus;
} driver_t;

driver_t* driver_new();

void driver_delete(driver_t* driver);

void xmlParse(driver_t* driverSet[], const char * XMLFileName);

void print_function(driver_t* driver);