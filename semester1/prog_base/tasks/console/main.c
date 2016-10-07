#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
void makeColor(int x, int y)
{
    int normalX, normalY;
    if (x==1)
        normalX=1;
    else if (x==6)
        normalX=2;
    else if (x==11)
        normalX=3;
    else if (x==16)
        normalX=4;
    else if (x==21)
        normalX=5;

    if (y==1)
        normalY=1;
    else if (y==11)
        normalY=2;
    else if (y==21)
        normalY=3;
    else if (y==31)
        normalY=4;
    else if (y==41)
        normalY=5;
    else if (y==51)
        normalY=6;
    else if (y==61)
        normalY=7;
    else if (y==71)
        normalY=8;

    if (normalX==normalY)
        printf("\033[44m");
    else if (normalX+3==normalY)
        printf("\033[44m");
    else if (normalY-1==normalX)
        printf("\033[46m");
    else if (normalX+2==normalY)
        printf("\033[46m");
    else
        printf("\033[42m");

}
void makeFigure(int x, int y)
{
    int i,j;
    makeColor(x,y);
    for (i=x; i<x+5; i++)
    {
        for (j=y; j<y+10; j++)
        {
            printf("\033[%i;%iH*", i, j);
        }
    }
}
int main()
{
    int i, j;
    int twoness=1;
    printf("Please print something to start the program: ");
    scanf("%i", &i);
    printf("\033[1;1H");
    for (i=1; i<=25; i++)
    {
        for (j=1; j<=80; j++)
        {
            printf("\033[%i;%iH ", i, j);
        }
    }
    printf("\033[1;1H");
    for (j=71; j>0; j-=10)
    {
        if (twoness == 1)
        {
            for (i=1; i<=21; i+=5)
            {
                usleep(100000);
                makeFigure(i,j);
            }
            twoness = 0;
        }
        else{
            for (i=21; i>=1; i-=5)
            {
                usleep(100000);
                makeFigure(i,j);
            }
            twoness = 1;
        }
    }
    printf("\033[40m");
    printf("\033[82;1H");
    return 0;
}
