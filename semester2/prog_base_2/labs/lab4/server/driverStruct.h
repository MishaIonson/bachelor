/* Investor struct with opened body.
This file is needed for proper incapsulation of data. */

#ifndef INVESTORSTRUCT_H_INCLUDED
#define INVESTORSTRUCT_H_INCLUDED

#include <time.h> //struct tm

struct driver_s {
	int id;
	char* name;
	char* nickname;
	char* surname;
	float way;
	//birthday date struct
	struct tm birthday;
	int exp;
	int salary;
	char * busName;
};

#endif // INVESTORSTRUCT_H_INCLUDED
