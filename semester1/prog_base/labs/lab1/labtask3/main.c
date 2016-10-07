#include <stdio.h>
#include <stdlib.h>
#include "math.h"


int sizeOfNum(int a, int b)
{
    int so;
    switch(abs(b) % 8)
    {
        case 0:
        {
            so=sizeof(char);
            break;
        }
        case 1:
        {
            so=sizeof(signed char);
            break;
        }
        case 2:
        {
            so=sizeof(short);
            break;
        }
        case 3:
        {
            so=sizeof(unsigned int);
            break;
        }
        case 4:
        {
            so=sizeof(long);
            break;
        }
        case 5:
        {
            so=sizeof(unsigned long long);
            break;
        }
        case 6:
        {
            so=sizeof(float);
            break;
        }
        case 7:
        {
            so=sizeof(double);
            break;
        }
    }
    return(abs(a)*so);
}

int exec (int op, int a, int b)
{
    int answer;
    if (op<0)
    {
        a=a-b;
        b=b+a;
        a=b-a;
    }

    switch(op)
    {
        case 0:
        {
            answer=(-1)*a;
            break;
        }
        case 1:
        {
            answer=a+b;
            break;
        }
        case 2:
        {
            answer=a-b;
            break;
        }
        case 3:
        {
            answer=a*b;
            break;
        }
        case 4:
        {
            if (b!=0)
            answer=a/b;
            else
            answer=0;
            break;
        }
        case 5:
        {
            answer=abs(a);
            break;
        }
        case 6:
        {
            answer=pow(a,b);
            break;
        }
        case 13:
        case 77:
        case 7:
        {
            answer=a%b;
            break;
        }
        case 8:
        {
            answer=fmax(a,b);
            break;
        }
        case 9:
        {
            answer=fmin(a,b);
            break;
        }
        case 10:
        {
            answer=sizeOfNum(a,b);
            break;
        }
        case 11:
        {
            if (b!=0)
            answer = M_PI * ( (a + b) % 11) / b;
            else
            answer=0;
            break;
        }
        default:
        {
            if (op < 100)
            answer = (op % abs(a+1)) + (op % abs(b+1));
            if (op >= 100)
            answer = -1;
            break;
        }
    }
    return answer;
}
int main()
{
    int x = exec(9, 4, -10);
    printf("%i", x);
}
