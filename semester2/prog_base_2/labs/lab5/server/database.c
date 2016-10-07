#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "database.h"
#include "driverStruct.h"
#include "invArrStruct.h"

struct database_s {
	sqlite3 * database;
};

database_t * database_new(const char * databaseFilename) {
	database_t * databaseSmp = malloc(sizeof(struct database_s));
	int rc = sqlite3_open(databaseFilename, &databaseSmp->database); // rc stands for 'errorCode'
	if (rc == SQLITE_ERROR) {
		printf("No such database exists.\n");
		exit(1); //	Exit instead of return to instantly abort the running program
	}
	return databaseSmp;
}

void database_free(database_t * self) {
	sqlite3_close(self->database);
	free(self);
}

// Amount of drivers in database.
// The function is not used in other files, so it's static.
static int database_getSize(const database_t * self) {
	sqlite3_stmt * stmt = NULL; // stmt stands for 'Prepared statement'
	char * sqlRequest = "SELECT COUNT(*) From Driver,DriverIden WHERE Driver.ID = DriverIden.IDinv;";
	sqlite3_prepare_v2(self->database, sqlRequest, strlen(sqlRequest) + 1, &stmt, NULL);

	int rc = sqlite3_step(stmt);
	if (rc == SQLITE_ERROR) {
		printf("Cannot get size of driver table.\n");
		exit(1); //	Exit instead of return to instantly abort the running program
	}
	int size = sqlite3_column_int(stmt, 0);
	sqlite3_finalize(stmt);
	return size;
}

// Fills single driver with the info from stmt.
// The function is not used in other files, so it's static.
static void driver_fillByStmt(sqlite3_stmt * stmt, driver_t * self) {
	// Main table
	int id = sqlite3_column_int(stmt, 0);
	double rate = sqlite3_column_double(stmt, 1);
	char * date = sqlite3_column_text(stmt, 2);
	int exp = sqlite3_column_int(stmt, 3);
	int salary = sqlite3_column_int(stmt, 4);
	char * busName = sqlite3_column_text(stmt, 5);
	// Sub-table
	char * nm = sqlite3_column_text(stmt, 6);
	char * nknm = sqlite3_column_text(stmt, 7);
	char * srnm = sqlite3_column_text(stmt, 8);

	self->id = id;
	self->way = (float)rate;
	// Date struct
	self->birthday.tm_year = atoi(date);
	date = strtok(date, "-");
	date = strtok(NULL, "-");
	self->birthday.tm_mday = atoi(date);
	date = strtok(NULL, "-");
	self->birthday.tm_mon = atoi(date);
	//
	self->exp = exp;
	self->salary = salary;
	strcpy(self->busName, busName);
	strcpy(self->name, nm);
	strcpy(self->nickname, nknm);
	strcpy(self->surname, srnm);
}

// Function that check whether there is an driver with such ($ID) in the database.
// @Returns: INDEX_COR from ERR_HNDL enum if the index presents, INDEX_INCOR otherwise.
ERR_HNDL database_isThereID(const database_t * self, int ID) {
	sqlite3_stmt * stmt = NULL;
	char * sqlRequest = "SELECT COUNT(*) From Driver,DriverIden WHERE Driver.ID = ? AND Driver.ID = DriverIden.IDinv;";
	sqlite3_prepare_v2(self->database, sqlRequest, strlen(sqlRequest) + 1, &stmt, NULL);

	sqlite3_bind_int(stmt, 1, ID);

	int rc = sqlite3_step(stmt);
	if (rc == SQLITE_ERROR) {
		printf("Cannot get info From Driver table.\n");
		exit(1); //	Exit instead of return to instantly abort the running program
	}
	int size = sqlite3_column_int(stmt, 0);

	sqlite3_finalize(stmt);
	// driver presents in database
	if (size == 1) {
		return INDEX_COR;
	}
	// driver does not present in database
	else if (size == 0) {
		return INDEX_INCOR;
	}
}

// Forms a single string From Driver 'struct tm date'
// The function is not used in other files, so it's static.
static char * driver_createStringFromDate(char * resultStr, driver_t * self) {
	sprintf(resultStr, "%d-%d-%d\n", self->birthday.tm_year, self->birthday.tm_mday, self->birthday.tm_mon);
	return resultStr;
}

// Creates a new driver in database with the info provided by invPtr.
void database_createInv(database_t * self, driver_t * invPtr) {
	// Main table
	sqlite3_stmt * stmt = NULL;
	char * sqlRequest = "INSERT INTO Driver ('way', 'birthday', 'exp', 'salary', 'busName') VALUES (?, ?, ?, ?, ?);";
	sqlite3_prepare_v2(self->database, sqlRequest, strlen(sqlRequest) + 1, &stmt, NULL);

	// |SQLITE_STATIC| in (sqlite3_bind_text) means that the given string does not need to be free()'d
	// |-1| in (sqlite3_bind_text) means auto-estimation of the length of the given string
	sqlite3_bind_double(stmt, 1, (double)invPtr->way);
	// Date struct
	char date[20];
	char * res = driver_createStringFromDate(date, invPtr);
	sqlite3_bind_text(stmt, 2, res, -1, SQLITE_STATIC);
	//
	sqlite3_bind_int(stmt, 3, invPtr->exp);
	sqlite3_bind_int(stmt, 4, invPtr->salary);
	sqlite3_bind_text(stmt, 5, invPtr->busName, -1, SQLITE_STATIC);

	int rc = sqlite3_step(stmt);
	if (rc == SQLITE_ERROR) {
		printf("Cannot create new driver.\n");
	}
	else {
		// Sub-table
		sqlite3_stmt * stmtIden = NULL;
		sqlRequest = "INSERT INTO DriverIden ('name', 'nickname', 'surname') VALUES (?, ?, ?);";
		sqlite3_prepare_v2(self->database, sqlRequest, strlen(sqlRequest) + 1, &stmtIden, NULL);

		sqlite3_bind_text(stmtIden, 1, invPtr->name, -1, SQLITE_STATIC);
		sqlite3_bind_text(stmtIden, 2, invPtr->nickname, -1, SQLITE_STATIC);
		sqlite3_bind_text(stmtIden, 3, invPtr->surname, -1, SQLITE_STATIC);

		int rc = sqlite3_step(stmtIden);
		if (rc == SQLITE_ERROR) {
			printf("Cannot create new driver sub-info.\n");
		}
		else {
			sqlite3_finalize(stmt);
			sqlite3_finalize(stmtIden);
		}
	}
}

// Returns a single driver from the database by certain index or NULL if such index does not exist.
// Free an driver with (driver_free() ) after you're finished with him!
driver_t * database_getInvFromDB(const database_t * self, int index) {
	sqlite3_stmt * stmt = NULL;
	driver_t * invSmp = driver_new();
	
	char * sqlRequest = "SELECT * From Driver,DriverIden WHERE ID = ? AND Driver.ID = DriverIden.IDinv;";
	sqlite3_prepare_v2(self->database, sqlRequest, strlen(sqlRequest) + 1, &stmt, NULL);
	sqlite3_bind_int(stmt, 1, index);

	int rc = sqlite3_step(stmt);
	if (rc == SQLITE_ERROR) {
		printf("Cannot get driver with this ID.\n");
		return NULL;
	}

	driver_fillByStmt(stmt, invSmp);
	sqlite3_finalize(stmt);
	return invSmp;
}

// Returns (new) invArr of drivers from database.
// Free returned invArr with invArr_free() after you're finished with it!
invArr_t * database_getInvListFromDB(const database_t * self) {
	sqlite3_stmt * stmt = NULL;
	int size = database_getSize(self);

	char * sqlRequest = "SELECT * From Driver,DriverIden WHERE Driver.ID = DriverIden.IDinv;";
	sqlite3_prepare_v2(self->database, sqlRequest, strlen(sqlRequest) + 1, &stmt, NULL);

	invArr_t * invArrToReturn = invArr_new();
	for (int i = 0; i < size; i++) { // Check on 'sqlite_done' is not needed as far as for() cycle works EXACTLY as much times, as needed
		int rc = sqlite3_step(stmt);
		if (rc == SQLITE_ERROR) {
			printf("Cannot get driver table.\n");
			exit(1); // Exit instead of return to instantly abort the running program
		}
		else {
			list_push_back(invArrToReturn->drivers, driver_new());
			driver_fillByStmt(stmt, (driver_t *)list_get(invArrToReturn->drivers, i));
		}
	}
	sqlite3_finalize(stmt);
	return invArrToReturn;
}

// Returns (new) invArr of drivers in database according to the given conditions.
// Free returned invArr with invArr_free() you're finished with it!
invArr_t * database_getInvArrFromDB_WHERE(const database_t * self, int salary, condition salarySign, int exp, condition expSign) {
	// Condition, given by user
	char mnySign;
	char xpSign;
	if (salarySign == GREATER) {
		mnySign = '>';
	}
	else if (salarySign == LESS) {
		mnySign = '<';
	}
	if (expSign == GREATER) {
		xpSign = '>';
	}
	else if (expSign == LESS) {
		xpSign = '<';
	}
	//

	// The amount of drivers that fit the condition
	sqlite3_stmt * stmt = NULL;
	char * sqlRequestSize = calloc(500, sizeof(char));
	sprintf(sqlRequestSize,
		"SELECT COUNT(*) From Driver,DriverIden "
		"WHERE (salary %c ? OR exp %c ?) "
		"AND Driver.ID = DriverIden.IDinv;",
		mnySign, xpSign);

	sqlite3_prepare_v2(self->database, sqlRequestSize, strlen(sqlRequestSize) + 1, &stmt, NULL);
	sqlite3_bind_int(stmt, 1, salary);
	sqlite3_bind_int(stmt, 2, exp);
	int rc = sqlite3_step(stmt);
	if (rc == SQLITE_ERROR) {
		free(sqlRequestSize);
		printf("Cannot get size of driver table.\n");
		exit(1); //	Exit instead of return to instantly abort the running program
	}
	int sizeFilter = sqlite3_column_int(stmt, 0);
	//

	sqlite3_reset(stmt);

	// Working with every single driver and his info
	char * sqlRequestdrivers = calloc(500, sizeof(char));
	sprintf(sqlRequestdrivers,
		"SELECT * From Driver,DriverIden "
		"WHERE (salary %c ? OR exp %c ?) "
		"AND Driver.ID = DriverIden.IDinv;",
		mnySign, xpSign);

	sqlite3_prepare_v2(self->database, sqlRequestdrivers, strlen(sqlRequestdrivers) + 1, &stmt, NULL);
	sqlite3_bind_int(stmt, 1, salary);
	sqlite3_bind_int(stmt, 2, exp);
	invArr_t * invToReturn = invArr_new();
	for (int i = 0; i < sizeFilter;i++) { // Check on 'sqlite_done' is not needed as far as for() cycle works EXACTLY as much times, as needed
		rc = sqlite3_step(stmt);
		if (rc == SQLITE_ERROR) {
			free(sqlRequestSize);
			free(sqlRequestdrivers);
			printf("Cannot get driver table.\n");
			exit(1); // Exit instead of return to instantly abort the running program
		}
		else {
			list_push_back(invToReturn->drivers, driver_new());
			driver_fillByStmt(stmt, (driver_t *)list_get(invToReturn->drivers, i));
		}
	}
	free(sqlRequestSize);
	free(sqlRequestdrivers);
	sqlite3_finalize(stmt);
	//

	return invToReturn;
}

// Function that deletes the driver by certain ID. IDs are not shifted (read description below).
// Description:
// For example, if you have 3 drivers with 1,2,3 indeces and then delete the 2nd one, the 1st and 3rd will remain.
// Then, when you add new another driver, it will be added with 4th index.
void database_deleteInv(database_t * self, int index) {
	// Main table
	sqlite3_stmt * stmt = NULL;
	char * sqlRequest = "DELETE From Driver WHERE ID = ?;";
	sqlite3_prepare_v2(self->database, sqlRequest, strlen(sqlRequest) + 1, &stmt, NULL);

	// Taking the ID to check which driver to delete ('WHERE ID = ?')
	sqlite3_bind_int(stmt, 1, index);
	int rc = sqlite3_step(stmt);
	if (rc == SQLITE_ERROR) {
		printf("Cannot delete this driver.\n");
	}
	else {
		// Sub-table
		sqlite3_stmt * stmtIden = NULL;
		sqlRequest = "DELETE From DriverIden WHERE IDinv = ?;";
		sqlite3_prepare_v2(self->database, sqlRequest, strlen(sqlRequest) + 1, &stmtIden, NULL);

		// Taking the ID to check which driver to delete ('WHERE ID = ?')
		sqlite3_bind_int(stmtIden, 1, index);
		int rc = sqlite3_step(stmtIden);
		if (rc == SQLITE_ERROR) {
			printf("Cannot delete this driver sub-info.\n");
		}
		else {
			sqlite3_finalize(stmt);
			sqlite3_finalize(stmtIden);
		}
	}
}