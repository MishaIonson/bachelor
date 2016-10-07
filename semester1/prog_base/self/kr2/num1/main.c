#include <stdio.h>
#include <stdlib.h>

int main()
{
    char nameIn[80];
    char nameOut[80];
    printf("Enter the name of input file: ");
    gets(nameIn);
    printf("Enter the name of output file: ");
    gets(nameOut);
    FILE *in = fopen(nameIn, "r");
    if (in!=NULL)
    {
        char line[10000];
        FILE *out = fopen("out.txt", "w");
        int i;
        while (fgets(line,1000, in))
        {
            for (i=0; i<strlen(line); i++)
            {
                if (( (int) line[i]>=65) && ((int) line[i]<=90))
                    fprintf(out, "%c", line[i]);
                else if ( ( (int) line[i]>=97) && ((int) line[i]<=122) )
                    fprintf(out, "%c", line[i]);
                else if ((i>0) && (( ((int)line[i-1]>=97) && ((int)line[i-1]<=122)) || (( (int) line[i]>=65) && ((int) line[i]<=90))) )
                    fprintf(out, "\n");
            }
        }
        fclose(in);



        fclose(out);
    }
    else
        printf("File is empty");

}
