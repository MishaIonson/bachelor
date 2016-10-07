#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "driverStruct.h"
#include "server.h"


//				Main function that analyses the path of the request.
//	It calls the described below functions basing on the path that request is sent to.

// @Returns (prints):		Proper answer to the client
void server_analyzeRequest(http_request_t * request, socket_t * client, database_t * db) {

	// HTML: homepage
	if (strcmp(request->uri, "/") == 0) {
		server_HTML_homepage(client, "Hello. Pls, proceed further to list of drivers (/drivers)"); // socket_close() function inside
	}

	// HTML: new-driver
	else if (strcmp(request->uri, "/new-driver") == 0 || strcmp(request->uri, "/new-driver/") == 0) {
		server_HTML_newdriver(db, client); // socket_close() function inside
	}

	// HTML: all drivers
	else if (strcmp(request->uri, "/drivers") == 0 || strcmp(request->uri, "/drivers/") == 0) {
		server_HTML_alldrivers(db, client, request); // socket_close() function inside
	}

	// HTML: single driver (by ID)
	// condition that is working with the index of the driver
	else if (strstr(request->uri, "/drivers/") != NULL && strstr(request->uri, "/api/drivers/") == NULL) {
		// checking if index is proper (i.e. is a number)
		char * token = strtok(request->uri, "/");
		token = strtok(NULL, "/");
		if (token != NULL && isdigit(token[0]) != 0) {
			// checking if index presents among our drivers
			int ID = atoi(token);
			if (database_isThereID(db, ID) == INDEX_COR) {
				server_HTML_driverByID(db, client, request, ID); // socket_close() function inside
			}
			// index does not present among our drivers
			else {
				server_invalidResponce(client, "Invalid path."); // socket_close() function inside
			}
		}
		// index is not proper (i.e. is not a number)
		else {
			server_invalidResponce(client, "Invalid path."); // socket_close() function inside
		}
	}


	// API: homepage
	else if (strcmp(request->uri, "/api") == 0 || strcmp(request->uri, "/api/") == 0) {
		server_API_homepage(client, "Hello. Pls, proceed further to list of drivers (/api/drivers)"); // socket_close() function inside
	}

	// API: all drivers
	else if (strcmp(request->uri, "/api/drivers") == 0 || strcmp(request->uri, "/api/drivers/") == 0) {
		server_API_alldrivers(db, client, request); // socket_close() function inside
	}
	// API: drivers with condition WHERE
	else if (strstr(request->uri, "/api/drivers/") == NULL && strstr(request->uri, "/api/drivers") != NULL) {
		int salary;
		condition salaryCond;
		int exp;
		condition expCond;
		char * token = strtok(request->uri, "/=?&");
		token = strtok(NULL, "/=?&");
		if (token != NULL && strcmp(token, "drivers") == 0) {
			token = strtok(NULL, "/=?&");
			// Is 'key' correct?:
			if (token != NULL && (strcmp(token, "salary_gt") == 0 || strcmp(token, "salary_lt") == 0 || strcmp(token, "exp_gt") == 0 || strcmp(token, "exp_lt") == 0)) {
				// If first condition is about salary...
				if (strcmp(token, "salary_gt") == 0 || strcmp(token, "salary_lt") == 0) {
					if (strcmp(token, "salary_gt") == 0) {
						salaryCond = GREATER;
					}
					else if (strcmp(token, "salary_lt") == 0) {
						salaryCond = LESS;
					}
					token = strtok(NULL, "/=?&");
					// Is 'value' correct?:
					if (token != NULL && isdigit(token[0]) != 0) {
						salary = atoi(token);
						// ...Then second condition must be about exp
						token = strtok(NULL, "/=?&");
						// Is 'key' correct?:
						if (token != NULL && (strcmp(token, "exp_gt") == 0 || strcmp(token, "exp_lt") == 0)) {
							if (strcmp(token, "exp_gt") == 0) {
								expCond = GREATER;
							}
							else if (strcmp(token, "exp_lt") == 0) {
								expCond = LESS;
							}
							token = strtok(NULL, "/=?&");
							// Is 'value' correct?:
							if (token != NULL && isdigit(token[0]) != 0) {
								exp = atoi(token);
								server_API_alldrivers_WHERE(db, client, request, salary, salaryCond, exp, expCond); // socket_close() function inside
							}
							else {
								server_invalidResponce(client, "Invalid path."); // socket_close() function inside
							}
						}
						else {
							server_invalidResponce(client, "Invalid path."); // socket_close() function inside
						}
					}
					else {
						server_invalidResponce(client, "Invalid path."); // socket_close() function inside
					}
				}
				// If first condition is about exp...
				else if (strcmp(token, "exp_gt") == 0 || strcmp(token, "exp_lt") == 0) {
					if (strcmp(token, "exp_gt") == 0) {
						expCond = GREATER;
					}
					else if (strcmp(token, "exp_lt") == 0) {
						expCond = LESS;
					}
					token = strtok(NULL, "/=?&");
					// Is 'value' correct?:
					if (token != NULL && isdigit(token[0]) != 0) {
						exp = atoi(token);
						// ...Then second condition must be about salary
						token = strtok(NULL, "/=?&");
						// Is 'key' correct?:
						if (token != NULL && (strcmp(token, "salary_gt") == 0 || strcmp(token, "salary_lt") == 0)) {
							if (strcmp(token, "salary_gt") == 0) {
								salaryCond = GREATER;
							}
							else if (strcmp(token, "salary_lt") == 0) {
								salaryCond = LESS;
							}
							token = strtok(NULL, "/=?&");
							// Is 'value' correct?:
							if (token != NULL && isdigit(token[0]) != 0) {
								salary = atoi(token);
								server_API_alldrivers_WHERE(db, client, request, salary, salaryCond, exp, expCond); // socket_close() function inside
							}
							else {
								server_invalidResponce(client, "Invalid path."); // socket_close() function inside
							}
						}
						else {
							server_invalidResponce(client, "Invalid path."); // socket_close() function inside
						}
					}
					else {
						server_invalidResponce(client, "Invalid path."); // socket_close() function inside
					}
				}
			}
		}
		else {
			server_invalidResponce(client, "Invalid path."); // socket_close() function inside
		}
	}

	// API: single driver (by ID)
	// condition that is working with the index of the driver
	else if (strstr(request->uri, "/api/drivers/") != NULL) {
		// checking if index is proper (i.e. is a number)
		char * token = strtok(request->uri, "/");
		token = strtok(NULL, "/");
		token = strtok(NULL, "/");
		if (token != NULL && isdigit(token[0]) != 0) {
			// checking if index presents among our drivers
			int ID = atoi(token);
			if (database_isThereID(db, ID) == INDEX_COR) {
				server_API_driverByID(db, client, request, ID); // socket_close() function inside
			}
			// index does not present among our drivers
			else {
				server_invalidResponce(client, "Invalid path."); // socket_close() function inside
			}
		}
		// index is not proper (i.e. is not a number)
		else {
			server_invalidResponce(client, "Invalid path."); // socket_close() function inside
		}
	}


	// HTML/API: default
	// default invalid path
	else {
		server_invalidResponce(client, "Invalid path."); // socket_close() function inside
	}

}


// ========================================FUNCTIONS THAT ARE USED IF YOU USE THE API FORM========================================

//						Root page of the server

// @Returns (prints):		Welcome message
void server_API_homepage(socket_t * client, char * message) {
	char strBuf[10240];

	sprintf(strBuf,
		"HTTP/1.1 200 OK\n"
		"Content-Type: text/html\n"
		"Content-Length: %zu\n"
		"Connection: keep-alive\n"
		"\n%s", strlen(message), message);

	socket_write_string(client, strBuf);
	socket_close(client);
}

// Command:					GET (for all drivers)			POST (for single driver)

// @Returns (prints):			all drivers						new driver			=====OR===== error message
void server_API_alldrivers(database_t * db, socket_t * client, http_request_t * req) {
	char strBuf[10240];

	// =====GET=====
	if (strcmp(req->method, "GET") == 0) {
		invArr_t * invArr = database_getInvListFromDB(db);
		char * invArrJSON = driver_parseAllToJSON(invArr);
		sprintf(strBuf,
			"HTTP/1.1 200 OK\n"
			"Content-Type: application/json\n"
			"Content-Length: %zu\n"
			"Connection: keep-alive\n"
			"\n%s", strlen(invArrJSON), invArrJSON);
		free(invArr);
		free(invArrJSON);
	}
	// =====POST=====
	else if (strcmp(req->method, "POST") == 0) {
		// ID field is assigned automatically in database.
		// Every new info is briefly checked on validity.
		// If some field is not valid - the driver is not added.
		driver_t * newdriver = driver_new();
		// Name field:
		char * str = http_request_getArg(req, "name");
		if (str != NULL && strlen(str) < 25) {
			strcpy(newdriver->name, str);
		}
		else {
			server_invalidResponce(client, "Invalid name.");
			return;
		}
		// Nickname field:
		str = http_request_getArg(req, "nickname");
		if (str != NULL && strlen(str) < 25) {
			strcpy(newdriver->nickname, str);
		}
		else {
			server_invalidResponce(client, "Invalid nickname.");
			return;
		}
		// Surname field:
		str = http_request_getArg(req, "surname");
		if (str != NULL && strlen(str) < 25) {
			strcpy(newdriver->surname, str);
		}
		else {
			server_invalidResponce(client, "Invalid surname.");
			return;
		}
		// way field:
		str = http_request_getArg(req, "way");
		if (str != NULL && isdigit(str[0]) != 0 && strlen(str) < 7) {
			newdriver->way = atof(str);
		}
		else {
			server_invalidResponce(client, "Invalid way.");
			return;
		}
		// First investment (date struct) field:
		str = http_request_getArg(req, "birthday");
		// Buffer for (str) string. First (str) will be checked on validity
		// and if everything is fine - the data will be copied again
		// and assigned to the fields.
		char buffForStr[30];
		strcpy(buffForStr, str);
		if (str != NULL) {
			// Checks if data of every field in date struct is valid:
			if (str[4] != NULL && str[4] == '-' && atoi(str) > 1900 && atoi(str) < 2016) {
				str = strtok(str, "-");
				str = strtok(NULL, "-");
				if (str != NULL && (atoi(str) >= 1 && atoi(str) <= 12)) {
					str = strtok(NULL, "-");
					if (str != NULL && (atoi(str) >= 1 && atoi(str) <= 31)) {
						// All data is valid:
						str = buffForStr;
						// Year:
						newdriver->birthday.tm_year = atoi(str);
						// Month:
						str = strtok(str, "-");
						str = strtok(NULL, "-");
						newdriver->birthday.tm_mon = atoi(str);
						// Day:
						str = strtok(NULL, "-");
						newdriver->birthday.tm_mday = atoi(str);
					}
					else {
						server_invalidResponce(client, "Invalid day.");
						return;
					}
				}
				else {
					server_invalidResponce(client, "Invalid month.");
					return;
				}
			}
			else {
				server_invalidResponce(client, "Invalid year.");
				return;
			}
		}
		// Experience field:
		str = http_request_getArg(req, "way");
		if (str != NULL && isdigit(str[0]) != 0 && atoi(str) >= 0) {
			newdriver->exp = atoi(str);
		}
		else {
			server_invalidResponce(client, "Invalid experience.");
			return;
		}
		// Total money invested field:
		str = http_request_getArg(req, "salary");
		if (str != NULL && isdigit(str[0]) != 0 && atoi(str) >= 0) {
			newdriver->salary = atoi(str);
		}
		else {
			server_invalidResponce(client, "Invalid money invested.");
			return;
		}
		// Current investment project field:
		str = http_request_getArg(req, "busName");
		if (str != NULL && strlen(str) < 100) {
			strcpy(newdriver->busName, str);
		}
		else {
			server_invalidResponce(client, "Invalid project.");
			return;
		}

		// Adding driver to database
		database_createInv(db, newdriver);

		char * newdriverJSON = driver_parseToJSON(newdriver);
		// Printing info to console.
		printf("New driver created:\n%s\n", newdriverJSON);
		// Giving info to the client.
		sprintf(strBuf,
			"HTTP/1.1 200 OK\n"
			"Content-Type: application/json\n"
			"Content-Length: %zu\n"
			"Connection: keep-alive\n"
			"\n%s", strlen(newdriverJSON), newdriverJSON);
		free(newdriver);
		free(newdriverJSON);
	}
	// =====Invalid command=====
	else {
		server_invalidResponce(client, "Invalid command.");
		return;
	}

	socket_write_string(client, strBuf);
	socket_close(client);
}

// Command:								GET (for all drivers)

// @Returns (prints):			all drivers (according to WHERE condition)			=====OR===== error message
void server_API_alldrivers_WHERE(database_t * db, socket_t * client, http_request_t * req, int salary, condition salarySign, int exp, condition expSign) {
	char strBuf[10240];

	// =====GET=====
	if (strcmp(req->method, "GET") == 0) {
		invArr_t * invWhereArr = database_getInvArrFromDB_WHERE(db, salary, salarySign, exp, expSign);
		char * invArrJSON = driver_parseAllToJSON(invWhereArr);
		sprintf(strBuf,
			"HTTP/1.1 200 OK\n"
			"Content-Type: application/json\n"
			"Content-Length: %zu\n"
			"Connection: keep-alive\n"
			"\n%s", strlen(invArrJSON), invArrJSON);
		free(invArrJSON);
		invArr_free(invWhereArr);
	}
	// =====Invalid command=====
	else {
		server_invalidResponce(client, "Invalid command.");
		return;
	}

	socket_write_string(client, strBuf);
	socket_close(client);
}

// Command:				GET						DELETE					For a single driver (by index)

// @Returns (prints): driver		message about successful deleting =====OR===== error message
void server_API_driverByID(database_t * db, socket_t * client, http_request_t * req, int ID) {
	char strBuf[10240];
	// =====GET=====
	if (strcmp(req->method, "GET") == 0) {
		driver_t * driver = database_getInvFromDB(db, ID);
		char * invJSON = driver_parseToJSON(driver);
		sprintf(strBuf,
			"HTTP/1.1 200 OK\n"
			"Content-Type: application/json\n"
			"Content-Length: %zu\n"
			"Connection: keep-alive\n"
			"\n%s", strlen(invJSON), invJSON);
		driver_free(driver);
		free(invJSON);
	}
	// =====DELETE=====
	else if (strcmp(req->method, "DELETE") == 0) {
		// Getting the driver (and his info) before it was deleted
		driver_t * deldriver = database_getInvFromDB(db, ID);
		// If something went wrong
		if (deldriver == NULL) {
			server_invalidResponce(client, "The driver was not deleted.");
			return;
		}
		// Deleting driver from database
		database_deleteInv(db, ID);

		char * deldriverJSON = driver_parseToJSON(deldriver);
		// Printing info to console.
		printf("Deleted driver (%i-th one):\n%s\n", ID, deldriverJSON);
		// Giving info to the client.
		char * delText = "driver deleted successfully!";

		sprintf(strBuf,
			"HTTP/1.1 200 OK\n"
			"Content-Type: application/json\n"
			"Content-Length: %zu\n"
			"Connection: keep-alive\n"
			"\n%s", strlen(delText), delText);

		free(deldriver);
		free(deldriverJSON);
	}
	// =====Invalid command=====
	else {
		server_invalidResponce(client, "Invalid command.");
		return;
	}
	socket_write_string(client, strBuf);
	socket_close(client);
}

// ========================================FUNCTIONS THAT ARE USED IF YOU USE THE HTML FORM========================================

//						Root page of the server

// @Returns (prints):		Welcome message
// (links):					alldrivers
void server_HTML_homepage(socket_t * client, char * message) {
	char strBuf[10240];

	char link[1024];
	strcpy(link, "<br/><a href=\"/drivers\">All drivers</a>");

	sprintf(strBuf,
		"HTTP/1.1 200 OK\n"
		"Content-Type: text/html\n"
		"Content-Length: %zu\n"
		"Connection: keep-alive\n"
		"\n%s%s", (strlen(message) + strlen(link)), message, link);
	socket_write_string(client, strBuf);
	socket_close(client);
}

// Command:								GET (for all drivers)						POST (for single driver)

// @Returns (prints):			all drivers (URLs, brief description)						new driver			=====OR===== error message
// (links):						each driver with full description (by ID)			HTML form to add new driver
void server_HTML_alldrivers(database_t * db, socket_t * client, http_request_t * req) {
	char strBuf[10240];

	// =====GET=====
	if (strcmp(req->method, "GET") == 0) {
		invArr_t * invArr = database_getInvListFromDB(db);
		char * line = driver_parseAllToHTML(invArr);

		char link[1024];
		strcpy(link, "<br/><a href=\"/new-driver\">New-driver</a>");

		sprintf(strBuf,
			"HTTP/1.1 200 OK\n"
			"Content-Type: text/html\n"
			"Content-Length: %zu\n"
			"Connection: keep-alive\n"
			"\n%s%s", (strlen(line) + strlen(link)), line, link);
		free(invArr);
		free(line);
	}

	// =====POST=====
	else if (strcmp(req->method, "POST") == 0) {
		// ID field is assigned automatically in database.
		// Every new info is briefly checked on validity.
		// If some field is not valid - the driver is not added.
		driver_t * newdriver = driver_new();
		// Name field:
		char * str = http_request_getArg(req, "name");
		if (str != NULL && strlen(str) < 25) {
			strcpy(newdriver->name, str);
		}
		else {
			server_invalidResponce(client, "Invalid name.");
			return;
		}
		// Nickname field:
		str = http_request_getArg(req, "nickname");
		if (str != NULL && strlen(str) < 25) {
			strcpy(newdriver->nickname, str);
		}
		else {
			server_invalidResponce(client, "Invalid nickname.");
			return;
		}
		// Surname field:
		str = http_request_getArg(req, "surname");
		if (str != NULL && strlen(str) < 25) {
			strcpy(newdriver->surname, str);
		}
		else {
			server_invalidResponce(client, "Invalid surname.");
			return;
		}
		// way field:
		str = http_request_getArg(req, "way");
		if (str != NULL && isdigit(str[0]) != 0 && strlen(str) < 7) {
			newdriver->way = atof(str);
		}
		else {
			server_invalidResponce(client, "Invalid way.");
			return;
		}
		// First investment (date struct) field:
		str = http_request_getArg(req, "birthday");
		// Buffer for (str) string. First (str) will be checked on validity
		// and if everything is fine - the data will be copied again
		// and assigned to the fields.
		char buffForStr[30];
		strcpy(buffForStr, str);
		if (str != NULL) {
			// Checks if data of every field in date struct is valid:
			if (str[4] != NULL && str[4] == '-' && atoi(str) > 1900 && atoi(str) < 2016) {
				str = strtok(str, "-");
				str = strtok(NULL, "-");
				if (str != NULL && (atoi(str) >= 1 && atoi(str) <= 12)) {
					str = strtok(NULL, "-");
					if (str != NULL && (atoi(str) >= 1 && atoi(str) <= 31)) {
						// All data is valid:
						str = buffForStr;
						// Year:
						newdriver->birthday.tm_year = atoi(str);
						// Month:
						str = strtok(str, "-");
						str = strtok(NULL, "-");
						newdriver->birthday.tm_mon = atoi(str);
						// Day:
						str = strtok(NULL, "-");
						newdriver->birthday.tm_mday = atoi(str);
					}
					else {
						server_invalidResponce(client, "Invalid day.");
						return;
					}
				}
				else {
					server_invalidResponce(client, "Invalid month.");
					return;
				}
			}
			else {
				server_invalidResponce(client, "Invalid year.");
				return;
			}
		}
		// Experience field:
		str = http_request_getArg(req, "way");
		if (str != NULL && isdigit(str[0]) != 0 && atoi(str) >= 0) {
			newdriver->exp = atoi(str);
		}
		else {
			server_invalidResponce(client, "Invalid experience.");
			return;
		}
		// Total money invested field:
		str = http_request_getArg(req, "totalsalaryested");
		if (str != NULL && isdigit(str[0]) != 0 && atoi(str) >= 0) {
			newdriver->salary = atoi(str);
		}
		else {
			server_invalidResponce(client, "Invalid money invested.");
			return;
		}
		// Current investment project field:
		str = http_request_getArg(req, "busName");
		if (str != NULL && strlen(str) < 100) {
			strcpy(newdriver->busName, str);
		}
		else {
			server_invalidResponce(client, "Invalid project.");
			return;
		}

		// Adding driver to our database
		database_createInv(db, newdriver);

		char * newdriverHTML = driver_parseToHTML(newdriver);
		// Printing info to console.
		printf("New driver created:\n%s\n", newdriverHTML);
		// Giving info to the client.
		sprintf(strBuf,
			"HTTP/1.1 200 OK\n"
			"Content-Type: text/html\n"
			"Content-Length: %zu\n"
			"Connection: keep-alive\n"
			"\n%s", strlen(newdriverHTML), newdriverHTML);
		free(newdriverHTML);
		free(newdriver);
	}

	// =====Invalid command=====
	else {
		server_invalidResponce(client, "Invalid command.");
		return;
	}

	socket_write_string(client, strBuf);
	socket_close(client);
}

// Command:								POST

// @Returns (prints):				new driver			=====OR===== error message
// (links):								--
void server_HTML_newdriver(database_t * db, socket_t * client) {
	char strbuf[10240];
	char line[1000];
	// the HTML form to send post request
	strcpy(line, "<html><head></head><body><form action=\"http://127.0.0.1:5000/drivers\" method=\"POST\">"
		"First Name:<br><input type=\"text\" name=\"name\" value='Ivan'><br>Nickname:<br>"
		"<input type=\"text\" name=\"nickname\" value='Vano'><br>"
		"Surname:<br><input type=\"text\" name=\"surname\" value=\"Ivanov\"><br>"
		"way:<br><input type=\"text\" name=\"way\" value=\"5.5\"><br>"
		"First investment date:<br><input type=\"text\" name=\"birthday\" value=\"1995-01-01\"><br>"
		"Experience in years:<br><input type=\"text\" name=\"way\" value=\"10\"><br>"
		"Total money invested (in $):<br><input type=\"text\" name=\"salary\" value=\"25000\"><br>"
		"Current investment project:<br><input type=\"text\" name=\"busName\" value=\"Memasiki\"><br>"
		"<input type=\"submit\" value='Send POST request' /></form></body></html>");

	sprintf(strbuf,
		"HTTP/1.1 200 OK\n"
		"Content-Type: text/html\n"
		"Content-Length: %zu\n"
		"Connection: keep-alive\n"
		"\n%s", strlen(line), line);

	socket_write_string(client, strbuf);
	socket_close(client);
}

// Command:						GET									DELETE					For a single driver (by index)

// @Returns (prints): driver (full description)		message about successful deleting =====OR===== error message
// (links):												link to delete the user with this ID
void server_HTML_driverByID(database_t * db, socket_t * client, http_request_t * req, int ID) {
	char strBuf[10240];

	// =====GET=====
	if (strcmp(req->method, "GET") == 0) {
		driver_t * driver = database_getInvFromDB(db, ID);
		char * line = driver_parseToHTML(driver);

		char link[1024];
		char linkURL[100];
		// the DELETE link with proper index
		sprintf(linkURL,
			"\"http://127.0.0.1:5000/drivers/%d\"",
			ID);

		// the main logic that the DELETE link consists of
		sprintf(link,
			"<br/><a href=\"#\" onclick=\"doDelete()\">Delete</a>"
			"<body><script>"
			"function doDelete() {"
			"var xhttp = new XMLHttpRequest();"
			"xhttp.open(\"DELETE\", %s, true);" // <-- %s (link) here -->
			"xhttp.send();}"
			"</script></body>",
			linkURL);// <-- link -->

		// info about the driver + delete link
		sprintf(strBuf,
			"HTTP/1.1 200 OK\n"
			"Content-Type: text/html\n"
			"Content-Length: %zu\n"
			"Connection: keep-alive\n"
			"\n%s%s", (strlen(line) + strlen(link)), line, link);
		free(driver);
		free(line);
	}

	// =====DELETE=====
	else if (strcmp(req->method, "DELETE") == 0) {
		// Getting the driver (and his info) before it was deleted
		driver_t * deldriver = database_getInvFromDB(db, ID);
		// If something went wrong
		if (deldriver == NULL) {
			server_invalidResponce(client, "The driver was not deleted.");
			return;
		}
		// Deleting the driver from database
		database_deleteInv(db, ID);

		char * deldriverHTML = driver_parseToHTML(deldriver);
		// Printing info to console.
		printf("Deleted driver (%i-th one):\n%s\n", ID, deldriverHTML);
		// Giving info to the client.
		char * delText = "driver deleted successfully!";

		sprintf(strBuf,
			"HTTP/1.1 200 OK\n"
			"Content-Type: text/html\n"
			"Content-Length: %zu\n"
			"Connection: keep-alive\n"
			"\n%s", strlen(delText), delText);

		free(deldriverHTML);
		free(deldriver);
	}

	// =====Invalid command=====
	else {
		server_invalidResponce(client, "Invalid command.");
		return;
	}

	socket_write_string(client, strBuf);
	socket_close(client);
}


// The function is used both in API and HTML requests.
//		Function that prints the given error message

// @Returns (prints):	error message
void server_invalidResponce(socket_t * client, char * message) {
	char strBuf[1024];
	char * errText = message;

	sprintf(strBuf,
		"HTTP/1.1 404 \n"
		"Content-Type: text/html\n"
		"Content-Length: %zu\n"
		"\n%s", strlen(errText), errText);

	socket_write_string(client, strBuf);
	socket_close(client);
}
