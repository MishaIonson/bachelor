#include "driver_json.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
cJSON * driver_mJSON(const driver * drivers)
{
    // for commit
    cJSON * driversJSON = cJSON_CreateObject();
	cJSON_AddItemToObject(driversJSON, "student", cJSON_CreateString(drivers->firstName));
	cJSON_AddItemToObject(driversJSON, "group", cJSON_CreateString(drivers->lastName));
	cJSON_AddItemToObject(driversJSON, "variant", cJSON_CreateNumber(drivers->id));
	return driversJSON;
}
char * driver_parseAllToJSON(const driver * driverArray, int size) {
	cJSON * driverArrayJSON = cJSON_CreateArray();
	int i;
	for ( i= 0; i < size; i++) {
		cJSON * tachJSON = driver_mJSON(driverArray + i);
		cJSON_AddItemToArray(driverArrayJSON, tachJSON);
	}
	char * bufferJSON = cJSON_Print(driverArrayJSON);
	cJSON_Delete(driverArrayJSON);
	return bufferJSON;
}

char * driver_parseToJSON(driver * self) {
//    printStruct(self);
    cJSON * teachJSON = driver_mJSON(self);
	char * bufferJSON = cJSON_Print(teachJSON);
	cJSON_Delete(teachJSON);
    return bufferJSON;
}
