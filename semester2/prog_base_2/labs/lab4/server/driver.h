/* driver.c/driver.h represent single driver structure (as object)
and the array of such objects - invArr structure
(contains list of drivers inside, represented with list.c/list.h).
These are the data we use to work with during the program.
Files also represent two functions that returns the line (of single driver OR their array (list):
in cJSON form (for API requests) or in HTML form (for HTML requests)
For more information check out driver.c file. */

#ifndef driver_H_INCLUDED
#define driver_H_INCLUDED

#include "list.h"

typedef struct driver_s driver_t;
typedef struct invArr_s invArr_t;

typedef enum {
	INDEX_COR = 1,
	INDEX_INCOR
} ERR_HNDL;

driver_t * driver_new(void);
void driver_free(driver_t * self);
void driver_fill(driver_t * self, int id, char * name, char * nickname, char * surname, float way, int year, int day, int month, int exp, int salary, char * busName);

invArr_t * invArr_new(void);
void invArr_free(invArr_t * self);

int invArr_seekForFreeID(const invArr_t * self);
void invArr_addInv(invArr_t * self, const driver_t * inv);
void invArr_addInvByIndex(invArr_t * self, const driver_t * inv, int index);

ERR_HNDL invArr_isThereID(const invArr_t * self, int ID);
driver_t * invArr_removeInvByID(invArr_t * self, int ID);
driver_t * invArr_getInvByID(const invArr_t * self, int ID);

int invArr_getSize(invArr_t * self);

// cJSON form
// Free a line after usage with built-in free() function!
char * driver_parseAllToJSON(const invArr_t * self);
// Free a line after usage with built-in free() function!
char * driver_parseToJSON(const driver_t * self);

// HTML form
// Free a line after usage with built-in free() function!
char * driver_parseAllToHTML(const invArr_t * self);
// Free a line after usage with built-in free() function!
char * driver_parseToHTML(const driver_t * self);

#endif //driver_H_INCLUDED
