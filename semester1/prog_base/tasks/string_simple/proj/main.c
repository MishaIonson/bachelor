#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *process(char *resultStr, const char *textLines[], int linesNum, const char *extraStr)
{
    int i;
    char *answer="";
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
void x(char *z[])
{
}
int main()
{
    char *z;;
    int a =52;
    sprintf(z, "%i", a);
    //itoa(a,z[0], 10);
    printf(z);
    return 0;
}
