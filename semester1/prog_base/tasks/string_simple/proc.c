#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *process(char *resultStr, const char *textLines[], int linesNum, const char *extraStr)
{
    int i;
    char a2[101];
    char *answer=&a2;
    int k=0;
    int number=0;
    for (i=0; i<linesNum; i++)
    {
        if (strlen(textLines[i]) <= 10)
        {
            number++;
            if (k!=0)
            {
                strcat(answer, extraStr);
                strcat(answer, textLines[i]);
            }
            else
                strcpy(answer, textLines[i]);

            k=1;
        }
    }
    sprintf(resultStr, "%i ", number);
    strcat(resultStr, answer);
    return resultStr;
}
