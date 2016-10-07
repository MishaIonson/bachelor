#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "driverStruct.h"
#include "server.h"

//				Main function that analyses the path of the request.
//	It calls the described below functions basing on the path that request is sent to.

// @Returns (prints):		Proper answer to the client
void server_analyzeRequest(http_request_t * request, socket_t * client, invArr_t * driverArray) {

	// HTML: homepage
	if (strcmp(request->uri, "/") == 0) {
		server_HTML_homepage(client, "<center>Put (/drivers) to see the list</center>"); // socket_close() function inside
	}

	// HTML: new-driver
	else if (strcmp(request->uri, "/new-driver") == 0 || strcmp(request->uri, "/new-driver/") == 0) {
		server_HTML_newdriver(driverArray, client); // socket_close() function inside
	}

	// HTML: all drivers
	else if (strcmp(request->uri, "/drivers") == 0 || strcmp(request->uri, "/drivers/") == 0) {
		server_HTML_alldrivers(driverArray, client, request); // socket_close() function inside
	}

	// HTML: single driver (by ID)
	// condition that is working with the index of the driver
	else if (strstr(request->uri, "/drivers/") != NULL && strstr(request->uri, "/api/drivers/") == NULL) {
		// checking if index is proper (i.e. is a number)
		char * string = strstr(request->uri, "/drivers/");
		char * token = strtok(request->uri, "/");
		token = strtok(NULL, "/");
		if (token != NULL && isdigit(token[0]) != 0) {
			// checking if index presents among our drivers
			int ID = atoi(token);
			if (invArr_isThereID(driverArray, ID) == INDEX_COR) {
				server_HTML_driverByID(driverArray, client, request, ID); // socket_close() function inside
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
		server_API_homepage(client, "<center>Put (/drivers) to see the list</center> (/api/drivers)"); // socket_close() function inside
	}

	// API: all drivers
	else if (strcmp(request->uri, "/api/drivers") == 0 || strcmp(request->uri, "/api/drivers/") == 0) {
		server_API_alldrivers(driverArray, client, request); // socket_close() function inside
	}

	// API: single driver (by ID)
	// condition that is working with the index of the driver
	else if (strstr(request->uri, "/api/drivers/") != NULL) {
		// checking if index is proper (i.e. is a number)
		char * string = strstr(request->uri, "/api/drivers/");
		char * token = strtok(request->uri, "/");
		token = strtok(NULL, "/");
		token = strtok(NULL, "/");
		if (token != NULL && isdigit(token[0]) != 0) {
			// checking if index presents among our drivers
			int ID = atoi(token);
			if (invArr_isThereID(driverArray, ID) == INDEX_COR) {
				server_API_driverByID(driverArray, client, request, ID); // socket_close() function inside
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
void server_API_alldrivers(invArr_t * self, socket_t * client, http_request_t * req) {
	char strBuf[10240];

	// =====GET=====
	if (strcmp(req->method, "GET") == 0) {
		char * invArrJSON = driver_parseAllToJSON(self);
		sprintf(strBuf,
			"HTTP/1.1 200 OK\n"
			"Content-Type: application/json\n"
			"Content-Length: %zu\n"
			"Connection: keep-alive\n"
			"\n%s", strlen(invArrJSON), invArrJSON);
		free(invArrJSON);
	}
	// =====POST=====
	else if (strcmp(req->method, "POST") == 0) {
		// ID field is assigned automatically.
		// Every new info is briefly checked on validity.
		// If some field is not valid - the driver is not added.
		driver_t * newdriver = driver_new();
		// Name field:
		char * str = http_request_getArg(req, "name");
		if (str != NULL && strlen(str) < 25) {
			newdriver->name = str;
		}
		else {
			server_invalidResponce(client, "Invalid name.");
			return;
		}
		// Nickname field:
		str = http_request_getArg(req, "nickname");
		if (str != NULL && strlen(str) < 25) {
			newdriver->nickname = str;
		}
		else {
			server_invalidResponce(client, "Invalid nickname.");
			return;
		}
		// Surname field:
		str = http_request_getArg(req, "surname");
		if (str != NULL && strlen(str) < 25) {
			newdriver->surname = str;
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
		str = http_request_getArg(req, "birthdayestmentDate");
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
		str = http_request_getArg(req, "experienceYears");
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
		str = http_request_getArg(req, "busNameest");
		if (str != NULL && strlen(str) < 100) {
			newdriver->busName = str;
		}
		else {
			server_invalidResponce(client, "Invalid project.");
			return;
		}

		// adding driver to our array (list)
		// (finding the proper ID for the driver)
		int newID = invArr_seekForFreeID(self);
		newdriver->id = newID;
		invArr_addInvByIndex(self, newdriver, newID);

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

// Command:				GET						DELETE					For a single driver (by index)

// @Returns (prints): driver		message about successful deleting =====OR===== error message
void server_API_driverByID(invArr_t * self, socket_t * client, http_request_t * req, int ID) {
	char strBuf[10240];
	// =====GET=====
	if (strcmp(req->method, "GET") == 0) {
		driver_t * driver = invArr_getInvByID(self, ID);
		char * invJSON = driver_parseToJSON(driver);
		sprintf(strBuf,
			"HTTP/1.1 200 OK\n"
			"Content-Type: application/json\n"
			"Content-Length: %zu\n"
			"Connection: keep-alive\n"
			"\n%s", strlen(invJSON), invJSON);
		free(invJSON);
	}
	// =====DELETE=====
	else if (strcmp(req->method, "DELETE") == 0) {
		driver_t * deldriver = invArr_removeInvByID(self, ID);
		// if something went wrong
		if (deldriver == NULL) {
			server_invalidResponce(client, "The driver was not deleted.");
			return;
		}

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
void server_HTML_alldrivers(invArr_t * self, socket_t * client, http_request_t * req) {
	char strBuf[10240];

	// =====GET=====
	if (strcmp(req->method, "GET") == 0) {
		char * line = driver_parseAllToHTML(self);

		char link[1024];
		strcpy(link, "<br/><a href=\"/new-driver\">New-driver</a>");

		sprintf(strBuf,
			"HTTP/1.1 200 OK\n"
			"Content-Type: text/html\n"
			"Content-Length: %zu\n"
			"Connection: keep-alive\n"
			"\n%s%s", (strlen(line) + strlen(link)), line, link);

		free(line);
	}

	// =====POST=====
	else if (strcmp(req->method, "POST") == 0) {
		// ID field is assigned automatically.
		// Every new info is briefly checked on validity.
		// If some field is not valid - the driver is not added.
		driver_t * newdriver = driver_new();
		// Name field:
		char * str = http_request_getArg(req, "name");
		if (str != NULL && strlen(str) < 25) {
			newdriver->name = str;
		}
		else {
			server_invalidResponce(client, "Invalid name.");
			return;
		}
		// Nickname field:
		str = http_request_getArg(req, "nickname");
		if (str != NULL && strlen(str) < 25) {
			newdriver->nickname = str;
		}
		else {
			server_invalidResponce(client, "Invalid nickname.");
			return;
		}
		// Surname field:
		str = http_request_getArg(req, "surname");
		if (str != NULL && strlen(str) < 25) {
			newdriver->surname = str;
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
		str = http_request_getArg(req, "birthdayestmentDate");
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
		str = http_request_getArg(req, "experienceYears");
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
		str = http_request_getArg(req, "busNameest");
		if (str != NULL && strlen(str) < 100) {
			newdriver->busName = str;
		}
		else {
			server_invalidResponce(client, "Invalid project.");
			return;
		}

		// Adding driver to our array (list)
		int newID = invArr_seekForFreeID(self);
		newdriver->id = newID;
		invArr_addInvByIndex(self, newdriver, newID);

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
void server_HTML_newdriver(invArr_t * self, socket_t * client) {
	char strbuf[10240];
	char line[1000];
	// the HTML form to send post request
	strcpy(line, "<html><head></head><body><form action=\"http://127.0.0.1:5000/drivers\" method=\"POST\">"
		"First Name:<br><input type=\"text\" name=\"name\" value='Kimi'><br>Nickname:<br>"
		"<input type=\"text\" name=\"nickname\" value='iceman'><br>"
		"Surname:<br><input type=\"text\" name=\"surname\" value=\"Raikkonen\"><br>"
		"Way:<br><input type=\"text\" name=\"way\" value=\"5.5\"><br>"
		"Birthday<br><input type=\"text\" name=\"birthdayestmentDate\" value=\"1980-11-21\"><br>"
		"Experience in years:<br><input type=\"text\" name=\"experienceYears\" value=\"12\"><br>"
		"Salary:<br><input type=\"text\" name=\"totalsalaryested\" value=\"200000\"><br>"
		"BusName:<br><input type=\"text\" name=\"busNameest\" value=\"The12\"><br>"
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
void server_HTML_driverByID(invArr_t * self, socket_t * client, http_request_t * req, int ID) {
	char strBuf[10240];

	// =====GET=====
	if (strcmp(req->method, "GET") == 0) {
		driver_t * driver = invArr_getInvByID(self, ID);
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

		free(line);
	}

	// =====DELETE=====
	else if (strcmp(req->method, "DELETE") == 0) {
		driver_t * deldriver = invArr_removeInvByID(self, ID);
		// if something went wrong
		if (deldriver == NULL) {
			server_invalidResponce(client, "The driver was not deleted.");
			return;
		}

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
