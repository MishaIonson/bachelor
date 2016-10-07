#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <math.h>
#include "snake_type.h"
void intro()
{
    FILE *in = fopen("records.txt", "r");
    char line[100];
    int i, num;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD position;
    position.X = 28;
    position.Y = 11;
    SetConsoleCursorPosition(hConsole, position);
    printf("Enter your nickname: ");

    gets(line);
    strcpy(User.name, line);

    cleanScreen();
    position.X = 20;
    position.Y = 11;
    SetConsoleCursorPosition(hConsole, position);
    printf("What you gonna do? Play(p), or see records(r): ");
    gets(line);
    if (line[0] == 'r')
    {
        cleanScreen();
        position.X = 1;
        position.Y = 1;
        SetConsoleCursorPosition(hConsole, position);
        fgets(line, 1000, in);
        num = line[0] - '0';
        for (i=0; i<num; i++)
        {
            fgets(line, 1000, in);
            printf("%s\n", line);
        }

        printf("\nPrint something to play: ");
        gets(line);
    }
    fclose(in);
    cleanScreen();
    position.X = 28;
    position.Y = 11;
    SetConsoleCursorPosition(hConsole, position);
    printf("Choose level(1-9): ");
    gets(line);
    num = line[0] - '0';
    User.speed = num;
}
