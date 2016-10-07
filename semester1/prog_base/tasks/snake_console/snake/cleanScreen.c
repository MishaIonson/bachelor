#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void cleanScreen()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD position;
	int i,j;
	for (i=0; i<79; i++)
	{
		for (j=0; j<24; j++)
		{
			position.X =i;
			position.Y = j;
			SetConsoleCursorPosition(hConsole, position);
			printf(" ");
		}
	}
}
