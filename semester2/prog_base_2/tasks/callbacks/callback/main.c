#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <windows.h>
#include <conio.h>

typedef void (*callback)(char *line, int , int);



void split(char *line, callback callback1, callback callback2)
{
	// определялка слова
    char c[100];
    int position = 0;
    int i = 0;
    int palindromNumber = 0;
    int cIndex = 0;
    while (line[i] != '\0')
    {
        strcpy(c[cIndex], line[i]);
        if (line[i] == ' ')
        {
            callback1(c[0], cIndex, position);
            position++;
            for (cIndex=0; cIndex<100; cIndex++)
                c[cIndex] = '\n';
            cIndex = -1;
        }
        cIndex++;
        i++;
    }
    // for the last word (with no SPACE after)
    callback1(c, cIndex, position);
}

void wordCB(char *line, int size, int position, callback cab)
{
    // определялка палиндрома
    int i, j;
    int isPalindrom = 1;
    for (i=0, j = size; i<=size/2, j>=size/2; i++, j--)
    {
        if (line[i]!=line[j])
        {
            isPalindrom = 0;
            break;
        }
    }
    if (isPalindrom==1)
    {
        cab(line, position, NULL);
    }
}

void main()
{
    wordCB('s', 1, 1, split);
    return;
}
