#ifndef DATABASE_H_INCLUDED
#define DATABASE_H_INCLUDED

#include "SQLite/sqlite3.h"

#include "driver.h"

typedef enum {
	LESS,
	GREATER
} condition;

typedef struct database_s database_t;

database_t * database_new(const char * databaseFilename);
void database_free(database_t * self);

ERR_HNDL database_isThereID(const database_t * self, int ID);
void database_createInv(database_t * self, driver_t * invPtr);
// Free an driver with (driver_free() ) after you're finished with him!
driver_t * database_getInvFromDB(const database_t * self, int index);
// Free returned invArr with invArr_free() after you're finished with it!
invArr_t * database_getInvListFromDB(const database_t * self);
// Free returned invArr with invArr_free() after you're finished with it!
invArr_t * database_getInvArrFromDB_WHERE(const database_t * self, int salary, condition salarySign, int exp, condition expSign);
void database_deleteInv(database_t * self, int index);

#endif //DATABASE_H_INCLUDED
