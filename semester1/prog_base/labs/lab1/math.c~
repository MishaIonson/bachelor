#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double calc(double x, double y, double z)
{
    double answer, a0, a1, a2;
    //long long retwisting;
    if ((z!=0) && (x-y!=0))
    a0=pow (x,(y+1))/(pow((x-y), 1/z));
    else
    return(NAN);

    if (x+y!=0)
    a1=y/(10*(x+y));
    if (x+y<0)
    a1*=-1;

    if ((x+y==0) || (sin(y)==0))
    return(NAN);

    if ((sin(y)>0) && (x>=0))
    a2=pow(x,(1/sin(y)));
    if ((sin(y)<0)  && (x>=0))
    a2=pow(x, (1/ ( (-1)*sin(y) )));

    if (x<0)
    return(NAN);

    answer = a0 + a1 + a2;

    return(answer);
}

int main()
{
    double d = calc (3.5, 2.5, -10);
    printf("%f", d);
}
