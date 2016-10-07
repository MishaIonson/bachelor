#include <stdio.h>
#include <stdlib.h>

void do_some(int n, int m1[], int m2[])
{
    int i;
    if (n<=0)
        return 0; // wtf
    int was=0;
    int min;
    for (i=0; i<n ; i++)
    {
        if (m1[i]+m2[i]>0)
        {
            printf("%i", m1[i]+m2[i]);
            if (was==0)
            {
                min = m1[i]+m2[i];
                was=1;
            }
            if (min>m1[i]+m2[i])
                min = m1[i]+m2[i];
        }
    }
    printf("/n");
    printf("Min: %i", min);
}
int main()
{
    printf("Hello world!\n");
    return 0;
}
