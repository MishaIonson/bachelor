#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int x[100];
int x_do()
{
    int i=0;
    for (i=0; i<100; i++)
    {
        x[i] = NAN;
    }
}
int count()
{
    int is_stop = 0;
    int i=-1;
    while(is_stop==0)
    {
        i++;
        if (x[i]==NAN)
        {
            is_stop=1;
        }
    }
    return i;
}

void push(int g)
{
    x[count()+1] = g;
}
int peek()
{
    return x[count()];
}
int pop(int index)
{
    int j;
    int answer = x[index];
    int size = count();
    for (j=index; j<size; j++)
    {
        x[j] = x[j+1];
    }
    return answer;
}
int main()
{
    // мы считаем, что массив уже того... задан:)
    printf("push=1, pop=2; peek=3, count=4\n");
    int g;
    scanf(&g);
    if (g==1)
    {
        scanf(&g);
        push(g);
        //printf("\n");
        printf("Done");
    }
    else if (g==2)
    {
        scanf(&g);
        //printf("\n");
        printf("%i ... Done", pop(g));
    }
    else if (g==3)
    {
        //printf("\n");
        printf("Done. %i", peek());
    }
    else if (g==4)
    {
        //printf("\n");
        printf("Done. %i", count());
    }

    return 0;
}
