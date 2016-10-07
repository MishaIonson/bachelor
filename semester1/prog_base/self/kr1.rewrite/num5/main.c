#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;

    int i,j;
    char line[20];
    printf("enter n: ");
    gets(line);
    n = line[0] - '0';
    int m1[n], m2[n];
    for (i=0; i<n; i++)
    {
        printf("enter m1: ");
        gets(line);
        m1[i] = line[0] - '0';
        printf("enter m2: ");
        gets(line);
        m2[i] = line[0] - '0';
    }
    printf("Result: \n");
    for (i=0; i<n; i++)
    {
        if (m1[i] - m2[i]<0)
        {
            printf("%i\n", m1[i] - m2[i]);
        }
    }
    return 0;
}
