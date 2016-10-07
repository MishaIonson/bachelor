#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "time.h"
#include "math.h"
struct m_size
{
    int h;
    int v;
};
extern int done;
enum the_command {MakeZero = 0, PutRandomNums, ChangeElement, DoVertical, PrintSumAll, PrintSumPart, Change1, Change2, Change3};
void operation(int command, int *mas[20][20], struct m_size size_data)
{
    int i,j;
    int num;
    int i1, i2;
    char line[10];
    if (command==MakeZero)
    {
        for (i=0; i<size_data.h; i++)
        {
            for (j=0; j<size_data.v; j++)
            {
                mas[i][j]=0;
            }
        }
    }
    else if (command==PutRandomNums)
    {
        int rangeMax;
        int rangeMin;
        clean_last_line();
        printf("Choose the range. Min: ");
        gets(line);
        sscanf(line, "%i", &rangeMin);
        if (check_num(rangeMin)!=1)
        {
            done=0;
        }

        clean_last_line();
        printf("Choose the range. Max: ");
        gets(line);
        sscanf(line, "%i", &rangeMax);
        if (check_num(rangeMax)!=1)
        {
            done=0;
        }
        srand(time(NULL));
        for (i=0; i<size_data.h; i++)
        {
            for (j=0; j<size_data.v; j++)
            {
                num = rand()%(rangeMax-rangeMin) + rangeMin;
                mas[i][j]=num;
            }
        }
    }
    else if (command==ChangeElement)
    {
        clean_last_line();
        printf("Choose string of: ");
        gets(line);
        sscanf(line, "%i", &i1);

        clean_last_line();
        printf("Choose column of: ");
        gets(line);
        sscanf(line, "%i", &i2);

        clean_last_line();
        printf("Enter the new temp: ");
        gets(line);
        sscanf(line, "%i", &num);
        if (check_num(num)!=1)
        {
            done=0;
        }
        mas[i1][i2] = num;
    }
    else if (command==DoVertical)
    {
        int mas2[size_data.h][size_data.v];
        for (i=0, i1=size_data.h-1; i<size_data.h, i1>=0; i++, i1--)
        {
            for (j=0; j<size_data.v; j++)
            {
                mas2[i1][j] = mas[i][j];
            }
        }
        for (i=0; i<size_data.h; i++)
        {
            for (j=0; j<size_data.v; j++)
            {
                mas[i][j]=mas2[i][j];
            }
        }
    }
    else if (command==PrintSumAll)
    {
        num=0;
        int need_m[20][20];

        for (i=0; i<size_data.h; i++)
        {
            for (j=0; j<size_data.v; j++)
            {
                need_m[i][j]=mas[i][j];
                num+=need_m[i][j];
            }
        }
        clean_last_line();
        printf("\033[21;35H");
        printf("Sum: %i\n", num);
        printf("\033[22;35H");
        printf("In a few seconds you may continue\n");
        usleep(1000000);
    }
    else if (command== PrintSumPart)
    {
        num=0;
        int need_m[20];
        clean_last_line();
        printf("Enter the string: ");
        gets(line);
        sscanf(line, "%i", &i1);
        if (i1<size_data.h)
        {
            for (i=0; i<size_data.v; i++)
            {
                need_m[i]=mas[i1][i];
                num+=need_m[i];
            }
            clean_last_line();
        printf("\033[21;35H");
        printf("Sum: %i\n", num);
        printf("\033[22;35H");
        printf("In a few seconds you may continue\n");
        usleep(1000000);
        }
        else{
            clean_last_line();
        printf("\033[22;19H");

            printf("Wrong string number. In a few seconds you may continue\n");
            printf("");
            usleep(1000000);
        }
    }
    else if (command == Change1)
    {
        clean_last_line();
        int maxE = mas[0][0];
        int minE = mas[0][0];
        i1 = 0;
        i2 = 0;
        int j1=0,j2=0;
        for (i=0; i<size_data.h; i++)
        {
            for (j=0; j<size_data.v; j++)
            {
                if (mas[i][j]>=maxE)
                {
                    maxE = mas[i][j];
                    i1 = i;
                    j1 = j;
                }
                if (mas[i][j]<minE)
                {
                    minE = mas[i][j];
                    i2 = i;
                    j2 = j;
                }
            }
        }
        num = mas[i1][j1];
        mas[i1][j1] = mas[i2][j2];
        mas[i2][j2] = num;
    }
    else if (command==Change2)
    {
        clean_last_line();
        int maxE = mas[0][0];
        int minE = mas[0][0];
        i1 = 0;
        i2 = 0;
        int j1=0,j2=0;
        for (i=0; i<size_data.h; i++)
        {
            for (j=0; j<size_data.v; j++)
            {
                if (mas[i][j]>maxE)
                {
                    maxE = mas[i][j];
                    i1 = i;
                    j1 = j;
                }
                if (mas[i][j]<=minE)
                {
                    minE = mas[i][j];
                    i2 = i;
                    j2 = j;
                }
            }
        }
        num = mas[i1][j1];
        mas[i1][j1] = mas[i2][j2];
        mas[i2][j2] = num;
    }
    else if (command == Change3)
    {
        clean_last_line();
        int maxS=0;
        int minS=0;
        for (i=0; i<size_data.v; i++)
        {
            num=0;
            for (j=0; j<size_data.h; j++)
            {
                num+=mas[j][i];
            }
            if (i==0)
            {
                maxS = num;
                minS = num;
            }
            else{
                if (num<minS)
                {
                    minS=num;
                    i2 = i;
                }
                if (num>maxS)
                {
                    maxS=num;
                    i1 = i;
                }
            }
        }
        int m[size_data.h];
        for (j=0 ; j<size_data.h; j++)
        {
            m[j]= mas[j][i1];
            mas[j][i1] = mas[j][i2];
            mas[j][i2] = m[j];
        }
    }
    else
    {
        clean_last_line();
        printf("\033[22;19H\033[41m");

            printf("There is no command like it. Try help\n");

            usleep(1000000);
    }
    //if (command==)
}
