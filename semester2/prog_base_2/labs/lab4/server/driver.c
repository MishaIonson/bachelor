#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "cJSON/cJSON.h"
#include "driverStruct.h"
#include "driver.h"

// ====================Single driver constructor (default values, ID == -1 )====================
driver_t * driver_new(void) {
	driver_t * invSmp = malloc(sizeof(struct driver_s));
	invSmp->id = -1;
	invSmp->name = "NoName";
	invSmp->nickname = "NoNickname";
	invSmp->surname = "NoSurname";
	invSmp->way = 0.0;
	//date
	memset(&(invSmp->birthday), 0, sizeof(invSmp->birthday));
	invSmp->birthday.tm_year = 1900;
	invSmp->birthday.tm_mday = 1;
	invSmp->birthday.tm_mon = 1;
	//
	invSmp->exp = 0;
	invSmp->salary = 0;
	invSmp->busName = "NobusName";
	return invSmp;
}

void driver_free(driver_t * self) {
	free(self);
}

void driver_fill(driver_t * self, int id, char * name, char * nickname, char * surname, float way, int year, int day, int month, int exp, int salary, char * busName) {
	self->id = id;
	self->name = name;
	self->nickname = nickname;
	self->surname = surname;
	self->way = way;
	//date
	self->birthday.tm_year = year;
	self->birthday.tm_mday = day;
	self->birthday.tm_mon = month;
	//
	self->exp = exp;
	self->salary = salary;
	self->busName = busName;
}

// ====================Array (list) with drivers====================
struct invArr_s {
	list_t * drivers;
};

invArr_t * invArr_new(void) {
	invArr_t * invArrSmp = malloc(sizeof(struct invArr_s));
	invArrSmp->drivers = list_new();
	return invArrSmp;
}

void invArr_free(invArr_t * self) {
	list_free(self->drivers);
	free(self);
}

// ==========Functions connected with adding the new driver to the list of drivers==========
// Function that returns the first free ID
int invArr_seekForFreeID(const invArr_t * self) {
	if (list_getSize(self->drivers) == 0) {
		return 0;
	}
	for (int i = 0; i <= list_getSize(self->drivers); i++) {
		if (i == list_getSize(self->drivers)) {
			return i;
		}
		else {
			driver_t * inv = (driver_t *)list_get(self->drivers, i);
			if (inv->id != i) {
				return i;
			}
		}
	}
}

// Function that adds new driver to the end of the list
void invArr_addInv(invArr_t * self, const driver_t * inv) {
	list_push_back(self->drivers, inv);
}

// Function that adds new driver to the some position ($index) to the list
void invArr_addInvByIndex(invArr_t * self, const driver_t * inv, int index) {
	list_insert(self->drivers, index, inv);
}

// ==========Functions connected with deleting the existing driver from the list of drivers==========
// Function that check whether there is an driver with such ($ID) in the list
// @Returns: INDEX_COR from ERR_HNDL enum if the index presents, INDEX_INCOR otherwise.
ERR_HNDL invArr_isThereID(const invArr_t * self, int ID) {
	for (int i = 0; i < list_getSize(self->drivers); i++) {
		driver_t * inv = (driver_t *)list_get(self->drivers, i);
		if (inv->id == ID) {
			return INDEX_COR;
		}
	}
	return INDEX_INCOR;
}

// Function that removes the driver by given ($ID)
driver_t * invArr_removeInvByID(invArr_t * self, int ID) {
	driver_t * inv = (driver_t *)list_remove(self->drivers, ID);
	return inv;
}

// Function that gets the driver by given ($ID)
driver_t * invArr_getInvByID(const invArr_t * self, int ID) {
	for (int i = 0; i < list_getSize(self->drivers); i++) {
		driver_t * inv = (driver_t *)list_get(self->drivers, i);
		if (inv->id == ID) {
			return inv;
		}
	}
	return NULL;
}

// ==========Other functions==========
int invArr_getSize(invArr_t * self) {
	return list_getSize(self->drivers);
}


// ====================Working with API (cJSON) requests====================

// Constructing a CJSON form from the single driver-struct
// The function is static as far as it is not used in other files.
static cJSON * driver_serializeJSON(const driver_t * self) {
    cJSON * invSmpJSON = cJSON_CreateObject();
	cJSON_AddItemToObject(invSmpJSON, "id", cJSON_CreateNumber(self->id));
	cJSON_AddItemToObject(invSmpJSON, "name", cJSON_CreateString(self->name));
	cJSON_AddItemToObject(invSmpJSON, "nickname", cJSON_CreateString(self->nickname));
	cJSON_AddItemToObject(invSmpJSON, "surname", cJSON_CreateString(self->surname));
	cJSON_AddItemToObject(invSmpJSON, "way", cJSON_CreateNumber(self->way));
	//date
	char data[20];
	sprintf(data, "%d-%d-%d", self->birthday.tm_year, self->birthday.tm_mon, self->birthday.tm_mday);
	cJSON_AddItemToObject(invSmpJSON, "birthdayestmentDate", cJSON_CreateString(data));
	//
	cJSON_AddItemToObject(invSmpJSON, "experienceYears", cJSON_CreateNumber(self->exp));
	cJSON_AddItemToObject(invSmpJSON, "totalsalaryested", cJSON_CreateNumber(self->salary));
	cJSON_AddItemToObject(invSmpJSON, "busNameest", cJSON_CreateString(self->busName));
	return invSmpJSON;
}

// Function that forms the line from the whole list of drivers that present in our program
// @Returns: line (constructed from all drivers from list) that is presented in cJSON form.
// Free a line after usage with built-in free() function!
char * driver_parseAllToJSON(const invArr_t * self) {
	cJSON * invArrJSON = cJSON_CreateArray();
	for (int i = 0; i < list_getSize(self->drivers); i++) {
		driver_t * invBuff = (driver_t *)list_get(self->drivers, i);
		cJSON * invJSON = driver_serializeJSON(invBuff);
		cJSON_AddItemToArray(invArrJSON, invJSON);
	}
	char * buffJSON = cJSON_Print(invArrJSON);
	cJSON_Delete(invArrJSON);
	return buffJSON;
}

// Function that forms the line from the single driver
// @Returns: line (constructed from one driver) that is presented in cJSON form.
// Free a line after usage with built-in free() function!
char * driver_parseToJSON(const driver_t * self) {
    cJSON * invJSON = driver_serializeJSON(self);
	char * buffJSON = cJSON_Print(invJSON);
	cJSON_Delete(invJSON);
    return buffJSON;
}

// ====================Working with HTML (HTML) requests====================

// Function that forms the line from the whole list of drivers that present in our program
// @Returns: line (constructed from all drivers from list) that is presented in HTML form.
// Free a line after usage with built-in free() function!
char * driver_parseAllToHTML(const invArr_t * self) {
	char * buffHTML = calloc(10000, sizeof(char));
	char buffdriver[1000];
	char buffURLdriver[100];
	// constructing (opening) a "carcass" for the HTML table (labels)
	sprintf(buffHTML,
		"<html><head></head><body><center><table border=\"1\">"
		"<tr><td>URL</td>"
		"<td>Name</td>"
		"<td>Surname</td></tr>");

	// inserting all drivers in this HTML table
	for (int i = 0; i < list_getSize(self->drivers); i++) {
		driver_t * invBuff = list_get(self->drivers, i);
		// link to the full description of driver
		sprintf(buffURLdriver,
			"<a href=\"/drivers/%d\">driver #%d</a>",
			invBuff->id, invBuff->id);

		// actually inserting all the info about driver into created HTML table
		sprintf(buffdriver,
			"<tr><td>%s</td>"
			"<td>%s</td>"
			"<td>%s</td></tr>",
			buffURLdriver, invBuff->name, invBuff->surname);
		strcat(buffHTML, buffdriver);
	}
	// closing a "carcass" for the HTML table
	strcat(buffHTML, "</table></center></body>");

	return buffHTML;
}


// Function that forms the line from the single driver
// @Returns: line (constructed from one driver) that is presented in HTML form.
// Free a line after usage with built-in free() function!
char * driver_parseToHTML(const driver_t * self) {
	char * buffHTML = calloc(10000, sizeof(char));
	// the simple HTML table with labels and one driver with full description inside
	sprintf(buffHTML,
		"<html><head></head><body><center><table border=\"1\">"
		"<tr><td>ID</td>"
		"<td>Name</td>"
		"<td>Nickname</td>"
		"<td>Surname</td>"
		"<td>way</td>"
		"<td>birthday</td>"
		"<td>Experience</td>"
		"<td>Salary</td>"
		"<td>BusName</td></tr>"
		"<tr><td>%d</td>"
		"<td>%s</td>"
		"<td>%s</td>"
		"<td>%s</td>"
		"<td>%.2f</td>"
		"<td>%d-%d-%d</td>"
		"<td>%d</td>"
		"<td>%d</td>"
		"<td>%s</td></tr>"
		"</table></center></body>",
		self->id, self->name,
		self->nickname, self->surname, self->way, self->birthday.tm_year,
		self->birthday.tm_mday, self->birthday.tm_mon, self->exp,
		self->salary, self->busName);

	return buffHTML;
}
