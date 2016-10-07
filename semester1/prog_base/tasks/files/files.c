#include <stdio.h>
#include <stdlib.h>

void fprocess(const char *pread, const char *pwrite)
{
    int i, index, j, line=1;
    int less_zero=0; // boolean
    int num[1000] = {0};
    char str[10000]={'s'};
    int answer, maxim;
    FILE *input = fopen(pread, "r");
    for (i=0; i<9; i++)
    {
        fgets(str, 1000, input);
    }
    fclose(input);
    i=0;
    line = str[i] - '0';
    i++;
    while(str[i]!=' ')
    {
        line = line*10 + str[i] - '0';
        i++;
    }
    index=0;
    i++;
    j=i;
    while(index<line)
    {
        less_zero = 0;
        if (str[i]=='-')
        {
            less_zero = 1; // true
            i++;
        }
        while((str[i]!=',') && (str[i]!='s'))
        {
            num[index] = num[index]*10 + str[i] - '0';
            i++;
        }
        if (less_zero==1)
        {
            num[index]*=-1;
        }
        index++;
        i++;
    }
    maxim = num[0];
    answer=0;
    for (i=1; i<index; i++)
    {
        if (maxim<num[i])
        {
            maxim = num[i];
            answer = i;
        }
    }
    FILE *out = fopen(pwrite, "w");
    fprintf(out, "%i\n", answer);
    fclose(out);
}
