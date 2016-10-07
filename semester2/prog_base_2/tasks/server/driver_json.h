#ifndef driver_JSON_H_INCLUDED
#define driver_JSON_H_INCLUDED
#include "driver.h"
#include "cJSON.h"
cJSON * driver_mJSON(const driver * drivers);
cJSON * driver_mJSON(const driver * drivers);
char * driver_parseToJSON(driver * self);
#endif // driver_JSON_H_INCLUDED
