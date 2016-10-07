#include <stdio.h>
#include <stdlib.h>
#include <time.h>
struct flower
{
    int hight;
    char name[20];
};
int count(int size, struct flower *f)
{
    int i, answer=0;
    for (i=0; i<size; i++)
    {
        if(f[i].hight>50)
            answer++;
    }
    return answer;
}
void change (struct flower *f, const char *newName)
{
    strcpy(f->name, newName);
}
void print(struct flower *f)
{
    int i,j;
    for (i=1; i<=25; i++)
    {
        for (j=1; j<=80; j++)
        {
            printf("\033[%i;%iH ", i, j);
        }
    }
    printf("\033[1;1H");
    for (i=0; i<10; i++)
    {
        printf("%i. %s, height: %i\n", i+1, f[i].name, f[i].hight);
    }
}
int main()
{
    srand(time(NULL));
    char line[30];
    struct flower f[10];
    int i;
    for (i=0; i<10; i++)
    {
        strcpy(f[i].name,"Ficus");
        f[i].hight = rand()%10 + 45;
    }
    print(&f);
    printf("\nNumber of flowers, have height>50: %i\n", count(10, &f));
    printf("Enter the index: ");
    gets(line);
    i = line[0] - '0';
    print(&f);
    printf("Enter new name: ");
    gets(line);
    strcpy(f[i-1].name, line);
    print(&f);
    return 0;
}
