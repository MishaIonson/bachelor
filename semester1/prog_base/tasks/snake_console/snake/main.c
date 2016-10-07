#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <math.h>
struct Snake
{
    char way;// LRFB
    int length;
    int ex_positions[80*25][2];
    int nowX;
    int nowY;
    int speed;
    char name[100];
};
struct user
{
    char name[100];
    int score;
    int lvl;
};
struct Apple
{
    int x;
    int y;
};
struct Snake User;
struct Apple apple;


void save_moving()
{
    int i,j;
    for (i=User.length-1; i>0; i--)
    {
        User.ex_positions[i][0] = User.ex_positions[i-1][0];
        User.ex_positions[i][1] = User.ex_positions[i-1][1];
    }
    User.ex_positions[0][0] = User.nowX;
    User.ex_positions[0][1] = User.nowY;
}
int dead_check()
{
    if ((User.nowX<0) || (User.nowX>=79) || (User.nowY<0) || (User.nowY>=23))
        return 1; // dead
    int i;
    for (i=1; i<User.length; i++)
    {
        if ((User.ex_positions[i][0] == User.nowX) && (User.ex_positions[i][1] == User.nowY))
            return 1; // dead
    }
    return 0; // alive
}
void do_moving()
{
    if (User.way=='F')
    {
        save_moving();
        User.nowY--;
    }
    else if (User.way=='L')
    {
        save_moving();
        User.nowX--;
    }
    else if (User.way=='R')
    {
        save_moving();
        User.nowX++;
    }
    else if (User.way=='B')
    {
        save_moving();
        User.nowY++;
    }
}
void drawing_screen()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD position;

    position.X = apple.x;
    position.Y = apple.y;
    SetConsoleCursorPosition(hConsole, position);
    printf("a");

	int i,j;
	for (i=0; i<80*25; i++)
	{
        if (User.ex_positions[i][0] == -10)
            break;
        else
        {
            position.X = User.ex_positions[i][0];
			position.Y = User.ex_positions[i][1];
			SetConsoleCursorPosition(hConsole, position);
			printf("#");
        }
	}

}

void save_records()
{
    FILE *in = fopen("records.txt", "r");
    int num,i, k;
    int userPos=-1;
    char line[1000];
    fscanf(in, "%s", line);
    num = line[0] - '0';
    struct user data[num];
    for (i=0; i<num; i++)
    {
        fscanf(in, "%s", line);
        strcpy(data[i].name, line);
        fscanf(in, "%s", line);
        data[i].score = line[0]-'0';
        if (data[i].score <=User.length)
            userPos = i;
        fscanf(in, "%s", line);
        data[i].lvl = line[0] - '0';
    }
    fclose(in);
    if (userPos==-1)
        userPos = num;
    FILE *out = fopen("records.txt", "w");
    fprintf(out, "%i\n", num+1);
    for (i=0; i<num+1; i++)
    {
        if (i<userPos)
        {
            fprintf(out, "%s\n", data[i].name);
            fprintf(out, "%i\n", data[i].score);
            fprintf(out, "%i\n", data[i].lvl);
            printf("%i.%s\n",i+1, data[i].name);
            printf("score: %i\n", data[i].score);
            printf( "level: %i\n", data[i].lvl);
        }
        else if (i == userPos)
        {
            fprintf(out, "%s\n", User.name);
            fprintf(out, "%i\n", User.length);
            fprintf(out, "%i\n", User.speed);
            printf("%i.%s\n",i+1, User.name);
            printf("score: %i\n", User.length);
            printf("level: %i\n", User.speed);
        }
        else if (i> userPos)
        {
            fprintf(out, "%s\n", data[i-1].name);
            fprintf(out, "%i\n", data[i-1].score);
            fprintf(out, "%i\n", data[i-1].lvl);
            printf("%i.%s\n",i+1, data[i-1].name);
            printf("score:%i\n", data[i-1].score);
            printf("level:%i\n", data[i-1].lvl);
        }
    }

    fclose(out);

}
void make_apple()
{
    int i;
    int done=0;
    while(done==0)
    {
        done=1;
        apple.x = rand()%78 + 1;
        apple.y = rand()%22+ 1;
        for (i=0; i<User.length; i++)
        {
            if ( (User.ex_positions[i][0]==apple.x) && (User.ex_positions[i][1]==apple.y) )
            {
                done=0;
            }
        }
    }

}
void was_eaten()
{
    if ( (User.nowX == apple.x) && (User.nowY == apple.y) )
    {
        User.length++;
        make_apple();
    }
}

void intro()
{
    printf("to control the snake use WASD\nto exit press e");
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
    int ask=1;
    while (ask)
    {
        system("cls");
        position.X = 20;
        position.Y = 11;

        SetConsoleCursorPosition(hConsole, position);
        printf("What you gonna do? Play(p), or see records(r): ");
        gets(line);
        if (line[0] == 'r')
        {
            system("cls");
            position.X = 1;
            position.Y = 1;
            SetConsoleCursorPosition(hConsole, position);
            fgets(line, 1000, in);
            num = line[0] - '0';
            for (i=0; i<num; i++)
            {
                printf("%i.", i+1);
                fgets(line, 1000, in);
                printf("%s", line);
                fgets(line, 1000, in);
                printf("score: %s", line);
                fgets(line, 1000, in);
                printf("level: %s\n", line);
            }

            printf("\nPrint something to start the game: ");
            gets(line);
            ask=0;
        }
        else if (line[0]=='p')
            ask=0;
    }


    fclose(in);
    num = 11;
    while((num<1) || (num>9))
    {
        system("cls");
        position.X = 28;
        position.Y = 11;
        SetConsoleCursorPosition(hConsole, position);
        printf("Choose level(1-9): ");
        gets(line);
        num = line[0] - '0';
        if (strlen(line)>1)
            num=10;
    }
    User.speed = num;
}





int main()
{
    srand(time(NULL));
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD position;
    int i,j;

    make_apple();
    for (i=0; i<80*25; i++)
    {
        User.ex_positions[i][0] = -10;
        User.ex_positions[i][1] = -10;
    }
    User.length=1;
    User.way = 'R';
    User.speed=1;
    User.ex_positions[0][0]=0;
    User.ex_positions[0][1]=0;
    User.nowX = 0;
    User.nowY = 0;
    intro();
    system("cls");

    char gottenKey;
    clock_t was = clock();
    while(1)
    {
        if (abs(was-clock())>100/ User.speed)
        {
            system("cls");
            do_moving();
            if (dead_check()==0)
                drawing_screen();
            else
                break;
            was = clock();
            was_eaten();
        }
        if (kbhit())
        {
            gottenKey = getch();
            if (gottenKey == 'w')
            {
                User.way = 'F';
            }
            else if (gottenKey == 's')
            {
                User.way = 'B';
            }
            else if (gottenKey == 'a')
            {
                User.way = 'L';
            }
            else if (gottenKey == 'd')
            {
                User.way = 'R';
            }
            else if (gottenKey == 'e')
                break;
        }

    }


    system("cls");
    position.X = 30;
    position.Y = 1;
    SetConsoleCursorPosition(hConsole, position);
    printf("You loose :( Score: %i\nRecords:\n", User.length);
    save_records();
    return 0;
}
