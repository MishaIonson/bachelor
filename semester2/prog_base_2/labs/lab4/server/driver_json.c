#include "driver_json.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
cJSON * driver_mJSON(const driver * drivers) {
    cJSON * driversJSON = cJSON_CreateObject();
	cJSON_AddItemToObject(driversJSON, "firstName", cJSON_CreateString(drivers->firstName));
	cJSON_AddItemToObject(driversJSON, "lastName", cJSON_CreateString(drivers->lastName));
	cJSON_AddItemToObject(driversJSON, "id", cJSON_CreateNumber(drivers->id));
	cJSON_AddItemToObject(driversJSON, "busName", cJSON_CreateString(drivers->driver_bus.busName));
	cJSON_AddItemToObject(driversJSON, "salary", cJSON_CreateNumber(drivers->salary));
	char date[20];
	sprintf(date, "%d-%d-%d", drivers->birthday.tm_year, drivers->birthday.tm_mon, drivers->birthday.tm_mday);
	cJSON_AddItemToObject(driversJSON, "birthday", cJSON_CreateString(date));
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
