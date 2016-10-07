#include <stdio.h>
#include <stdlib.h>

int main()
{
    char line[80];
    int i;
    for (i=0; i<80; i++)
    {
        line[i] = '*';
    }
    printf("Enter string: ");
    gets(line);
    int n=0;
    int first, last;
    first =0 ;
    printf("\nResult:\n");
    while(line[n]!='*')
    {
        if (line[n] == ' ')
        {
            if (n-first>5)
            {
                printf("%c%i%c",line[first], n-2-first, line[n-1]);
            }
            else
            {
                for (i=n-1; i>=first; i--)
                {
                    printf("%c", line[i]);
                }
            }
            first = n+1;
            printf("\n");
        }
        n++;
    }
    if (n-first>5)
    {
        printf("%c%i%c",line[first], n-3-first, line[n-2]);
    }
    else
    {
        for (i=n-1; i>=first; i--)
        {
            printf("%c", line[i]);
        }
    }
    return 0;
}
