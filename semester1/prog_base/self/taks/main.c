#include <stdio.h>
#include <stdlib.h>
#include <time.h>
struct Plane
{
    struct Plane *p1;
    int i;
};
void make_free(struct Plane *p)
{
    free(p);
}
int main()
{
    srand(time(NULL));
    int i, n;
    printf("Enter the size: ");
    scanf("%i", &n);
    struct Plane *a;
    a = malloc( sizeof(struct Plane)*n );
    printf("Generated: ");
    for (i=0; i<n; i++)
    {
        a[i].i = rand()%10;
        printf("%i ", a[i].i);
    }
    make_free(a);
    return 0;
}
