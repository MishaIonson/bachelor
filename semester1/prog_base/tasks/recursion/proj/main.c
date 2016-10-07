#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int first(const char str[], int i)
{
    if (i==strlen(str))
        return -1;
    if (str[i] !=' ')
    {
        return (int) str[i];
        }
    else
    {
        return first(str, i+1);
        }
}
int last(const char str[], int i)
{
    if (i==-1)
        return -1;
    if (str[i] !=' ')
    {
        return (int) str[i];
        }
    else
    {
        return last(str, i-1);
        }
}
int main()
{
    char str[1000000];
    printf("Enter string: ");
    gets(str);
    printf("Answer: %i", first(str, 0) + last(str, strlen(str) - 1));
    return 0;
}
