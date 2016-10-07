#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "time.h"
#include "math.h"
// Руслан Анатольевич! Она реально нужна, я отвечаю
int done=0;
struct m_size
{
    int h;
    int v;
};
enum the_command {MakeZero = 0, PutRandomNums, ChangeElement, DoVertical, PrintSumAll, PrintSumPart, Change1, Change2, Change3};
void explotion()
{
    int x,y,i;
    for (x=1; x<25; x++)
    {
        for (y=1; y<80; y++)
        {
            printf("\033[47m\033[%i,%iH ", x, y);
            if ((y==1) || (y==30) || (y==59))
            {
                printf("\033[30m\033[%i;%iHBOOM!!!", x, y);
            }
        }
    }
    //usleep(25000);
}
int check_num(int num)
{
    if (num>=100)
    {
        return 0; // has to stop
    }
    else if (num<-10)
    {
        return 0;
    }
    else{
        return 1; // it's ok
    }
}
void clean_last_line()
{
    int i;
    for (i=0; i<=80; i++)
    {
        if (i<34)
        {
             printf("\033[41m\033[23;%iH ",i);
        }
        else if (i>56)
        {
            printf("\033[41m\033[23;%iH ",i);
        }
        else{
            printf("\033[40m\033[23;%iH ",i);
        }
    }
    printf("\033[40m\033[23;34H");
}
struct m_size the_intro_talk()
{
    char name[40];
    printf("\033[41m");
    printf("\033[33m");
    printf("\033[1;33m");
    printf("\033[12;20H");
    int i, j;
    printf("NuclearReactor RB-9. \033[13;20HTemperature control\n");
    usleep(2500000);
    the_intro_color(2);
    printf("\033[12;33HUSSR 1975\n");
    usleep(2500000);
    the_intro_color(2);
    printf("\033[12;20H");
    printf("Hello, comrad! Enter the password: ");
    gets(name);
    for (i = 1; i<=25; i++)
    {
        for (j=1; j<=80; j++)
        {
            printf("\033[%i;%iH  ", i,j);
        }
    }
    if ((name[0]!='m') && (name[1]!='i') && (name[2]!='s') && (name[3]!='h') && (name[4]!='a'))
    {
        to_syberia();
        struct m_size k;
        k.h=1;
        k.v=1;
        return k;
    }
    int s,c; // columns and strings
    char line[10];
    printf("\033[41m");
    printf("\033[33m");
    printf("\033[1;33m");
    printf("\033[12;20H");
    printf("Please, enter the size of reactor. Strings: ");
    gets(line);
    sscanf(line, "%i", &s);
    the_intro_color(2);
    if (checking_lines(s)!=1)
    {
        the_intro_color(2);
        to_syberia();
        struct m_size k;
        k.h=1;
        k.v=1;
        return k;
    }

    printf("\033[41m");
    printf("\033[33m");
    printf("\033[1;33m");
    printf("\033[12;20H");
    printf("Please, enter the size of reactor. Columns: ");
    gets(line);
    sscanf(line, "%i", &c);
    if (checking_lines(c)!=1)
    {
        the_intro_color(2);
        to_syberia();
        struct m_size k;
        k.h=1;
        k.v=1;
        return k;
    }
    struct m_size answer;
    answer.h = s;
    answer.v = c;
    done=1;
    return answer;
}
void strings_swimming_down(char* str[], int size)
{
    int i,j;
    printf("\033[41m");
    printf("\033[33m");
    printf("\033[1;33m");
    printf("\033[12;20H");
    for (i=12; i<25; i++)
    {
        if (i!=1)
        {
            printf("\033[%i;36H", i-1);
            for (j=0; j<size; j++)
            {
                printf(" ");
            }
        }
        printf("\033[%i;36H", i);
        printf("%s", str);
        printf("\n");
        usleep(90000);
    }
}
void strings_swimming_up(char* str[], int size)
{
    int i,j;
    printf("\033[41m");
    printf("\033[33m");
    printf("\033[1;33m");
    printf("\033[12;20H");
    for (i=25; i>=1; i--)
    {
        printf("\033[%i;%iH", i+1, 40 - size/2);
        for (j=0; j<size; j++)
        {
            printf(" ");
        }
        printf("\033[%i;%iH", i, 40 - size/2);
        printf("%s", str);
        printf("\n");
        usleep(25000);
    }
}
void the_intro_color(int sizeficator)
{
    int i, j;
    printf("\033[41m");
    for (i = 1; i<=25; i++)
    {
        for (j=1; j<=80; j++)
        {
            printf("\033[%i;%iH ", i,j);
        }
    }
}
void show_matrix(int *mas[20][20], struct m_size size_data)
{
    int i,j;
    printf("\033[40m");
    for (i=8; i<=17; i++)
    {
        for (j=2; j<=66; j++)
        {
            printf("\033[%i;%iH ", i, j);
        }
    }
    for (i=1; i<=8; i++)
    {

        for (j=50; j<=55; j++)
        {
            printf("\033[%i;%iH ", i, j);
        }
    }
    for (i=48; i<=57; i++)
    {
        printf("\033[1;%iH ", i);
        if ((i!=48) && (i!=57))
        {
            printf("\033[7;%iH ", i);
        }
    }
    printf("\033[41m\033[10;65H ");
    printf("\033[41m\033[10;63H ");
    printf("\033[41m\033[10;61H ");
    printf("\033[40m\033[9;10H");
    for (i=0; i<size_data.h; i++)
    {
        for (j=0; j<size_data.v; j++)
        {
            printf("%i'C ", mas[i][j]);
        }
        printf("\033[%i;10H", i+10);
    }
    printf("\033[41m");

}
void to_syberia()
{
    printf("\033[12;36H");
    printf("W R O N G");
    usleep(25000);
    strings_swimming_down("W R O N G", 9);
    the_intro_color(2);
    int i, j;
    printf("\033[47m");
    for (i = 1; i<=25; i++)
    {
        for (j=1; j<=80; j++)
        {
            printf("\033[%i;%iH \n", i,j);

        }
        usleep(25000);
    }
    for (i=35; i<55; i++)
    {
        printf("\033[30m\033[9;%iH_", i);
    }
    printf("\033[10;35H\033[30mSay hello to Syberia");
    printf("\033[20;1H");
}
void print_commands()
{
    clean_last_line();
    printf("\033[41m");
    printf("\033[18;17H0 - stop reactor, 1 - make random temp\033[19;17H2 - set temp, 3 -  change vertical\033[20;17H4 - look the sum of temp, 5 - sum of string's elements\033[21;17H6-8 - some changing moves. Extra: help, exit.\n");

    printf("");
    usleep(2000000);
}
int checking_lines(int lines)
{
    if ((lines>8) || (lines<=1))
    {
        printf("\033[10;20HThere is no reactor with %i cores in line\n", lines);
        usleep(2000000);
        return 0;
    }
    else
    {
        return 1;
    }
}
int main()
{
    the_intro_color(2);
    struct m_size ms = the_intro_talk();
    int mas[20][20] = {1};
    char line[20];
    int com;
    while(done==1)
    {
        the_intro_color(2);
        show_matrix(&mas, ms);
        clean_last_line();
        printf("\033[23;35H");
        printf("Choose command: ");
        gets(line);
        sscanf(line, "%i", &com);
        if ((line[0] == 'e') && (line[1] == 'x') && (line[2] == 'i') && (line[3] == 't'))
            break;
        if ((line[0] == 'h') && (line[1] == 'e') && (line[2] == 'l') && (line[3] == 'p'))
        {
            print_commands();
        }
        else if (com==NAN)
        {
            clean_last_line();
        printf("\033[22;19H\033[41m");

            printf("There is no command like it. Try help\n");

            usleep(1000000);
        }
        else
        {
            sscanf(line, "%i", &com);
            operation(com, &mas, ms);
            show_matrix(&mas, ms);
        }
        if (done==0)
        {
            explotion();
        }
    }
    return 0;
}
