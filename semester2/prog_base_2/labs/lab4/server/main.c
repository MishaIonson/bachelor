#include <stdio.h>
#include <stdlib.h>

#include "server.h"

static socket_t * winSock;

int main()
{
    driver_t * drivers[3];
	invArr_t * driverArray = invArr_new();



	for (int i = 0; i < sizeof(drivers) / sizeof(drivers[0]); i++)
    {
		drivers[i] = driver_new();
	}
	driver_fill(drivers[0], 0, "Ayrton", "Witcher", "Senna", 8.9, 1950, 25, 9, 20, 10000000, "Williams");
	driver_fill(drivers[1], 1, "Michael", "RedBaron", "Schumacher", 5.6, 1970, 15, 3, 21, 1000000, "Ferrari");
	driver_fill(drivers[2], 2, "Seb", "Finger", "Vettel", 8.1, 1987, 20, 1, 10, 5000000, "RedBull");
	for (int i = 0; i < sizeof(drivers) / sizeof(drivers[0]); i++) {
		invArr_addInv(driverArray, drivers[i]);
	}

	int PORT = 5000;
	lib_init();
	winSock = socket_new();

	// Checking if socket is not busy, closing app if it is
	if (socket_bind(winSock, PORT) == SOCKET_ERR) {
		printf("Cannot bind %i port\n", PORT);
		socket_close(winSock);
		socket_free(winSock);
		return 0;
	}

	socket_listen(winSock);
	char buf[10000];
	socket_t * client = NULL;
	// main cycle of the program
	while (1) {
		printf("Waiting for connections...\n");
		client = socket_accept(winSock);

		// Checking if client is not null, closing app if he is
		if (client == NULL) {
			printf("NULL client, closing app...\n");
			break;
		}

		int readStatus = socket_read(client, buf, sizeof(buf));

		// Skipping empty request (may appear from time to time)
		if (readStatus <= 0) {
			printf("Empty request, skipping...\n");
			socket_close(client);
			socket_free(client);
			continue;
		}

		// Printing info about the received request to console
		printf(">> Got request (readStatus: %i):\n'%s'\n", readStatus, buf);
		http_request_t request = http_request_parse(buf);

		// check the type/path of request (API/HTML) & analyze the method (GET/POST/DELETE)
		// and provide the client with proper answer
		server_analyzeRequest(&request, client, driverArray);

		socket_free(client);
	}

	// end of program
	socket_close(winSock);
	socket_free(winSock);
	for (int i = 0; i < sizeof(drivers) / sizeof(drivers[0]); i++) {
		driver_free(drivers[i]);
	}
	invArr_free(driverArray);
	lib_free();
	return 0;
}
