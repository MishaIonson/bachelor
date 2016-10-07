#pragma once
#include <stdlib.h>
#include <time.h>


typedef enum DB_STATUS {
    DB_OK, DB_ERROR} DB_STATUS;

typedef struct driver_db_s driver_db_t;

typedef struct driver_s{
    int id;
    char name[20];
    char surname[20];
    int way;
    float salary;
    time_t birthday;

} driver_t;

driver_db_t * driver_db_new(const char * db_file);
void driver_db_delete(driver_db_t * self);

int driver_db_rows_count(driver_db_t * self);


void driver_db_add_driver(driver_db_t * self, driver_db_t * d);
driver_db_t * driver_db_get_driver(driver_db_t * self, int id);
void driver_db_update_driver(driver_db_t * self, driver_t * d);
void driver_db_delete_driver(driver_db_t * self, int id);


driver_t * driver_db_get_filtered_driver(driver_db_t * self, int driversCount, int wayP, size_t * pcount);

DB_STATUS driver_db_get_last_status();
