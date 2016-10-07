#include <stdio.h>
#include <stdlib.h>
#include "math.h"
double calc(int n, int m)
{
    double x =0;
    int i;
    int j;
    long long cos_par;
    for (i=1; i<=n; i++)
    {
        cos_par=0;
        for (j=1; j<=m; j++)
        {
            cos_par+=j*j;
        }
        x+=sin(2*M_PI/(i)) * cos (cos_par);
    }
    return x;
}
int main()
{
    double x = calc (12,2);
    printf("%f", x);
    return 0;
}
