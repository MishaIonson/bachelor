#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void fillRand1(int arr[], int size)
{
    int i;
    for (i = 0; i<size; i++)
    {
        arr[i] = 1 + rand() % 99;
    }
}

int checkRand1(int arr[], int size)
{
    int answer = 1;
    int i;

    for (i = 0; i<size; i++)
    {
        if ((arr[i]<1) || (arr[i]>99))
            answer = 0;
    }
    return answer;
}

float meanValue(int arr[], int size)
{
    float average=0;
    int i;
    for (i=0; i<size; i++)
    {
        average+= arr[i];
    }
    average/=size;
    return average;
}
int minValue(int arr[], int size)
{
    int min_value;
    int i = arr[0];
    for (i=1; i<size; i++)
    {
        if (arr[i]<min_value)
            min_value = arr[i];
    }
    return min_value;
}

int meanIndex(int arr[], int size)
{
    int answer = 0;
    float mv = meanValue(arr, size);
    float min_difference = abs(mv - arr[0]);
    int i;
    float average;
    for (i=1; i<size; i++)
    {
        if (abs(mv - arr[i]) < min_difference)
        {
            answer = i;
            min_difference = abs(mv - arr[i]);
        }
    }
    return answer;
}

int minIndex (int arr[], int size)
{
    int min_v = minValue(arr, size);
    int stop = 0;
    int answer;
    int i=0;
    while (stop==0)
    {
        if (min_v ==arr[i])
        {
            stop = 1;
            answer = i;
        }
        i++;
    }
}
int maxOccurance(int arr[], int size)
{
    int i;
    int val_num[size];
    for (i=0; i<size; i++)
    {
        val_num[i]=0;
    }
    int j;
    for (i=0; i< size; i++)
    {
        for (j=0; j< size; j++)
        {
            if (arr[i] == arr[j])
                val_num[i]++;
        }
    }
    int biggest = val_num[0];
    int answer = arr[0];
    for (i=0; i< size; i++)
    {
        if ((biggest < val_num[i]) || ((biggest == val_num[i]) && (answer < arr[i])))
        {
            biggest = val_num[i];
            answer = arr[i];
        }
    }
    return answer;
}

int diff(int arr1[], int arr2[], int res[], int size)
{
    int i;
    int answer = 1;
    for (i=0; i < size; i++)
    {
        res[i] = arr1[i] - arr2[i];
        if (res[i] !=0)
            answer = 0;
    }
    return answer;
}

void sub (int arr1[], int arr2[], int res[], int size)
{
    int i;
    for (i = 0; i<size; i++)
    {
        res[i] = arr1[i] - arr2[i];
    }
}

int qteg(int arr1[], int arr2[], int size)
{
    int i;
    for (i = 0; i<size; i++)
    {
        if (arr1[i] < arr2[i])
            return 0;
    }
    return 1;
}

void land(int arr1[], int arr2[], int res[], int size)
{
    int i;
    for (i=0; i<size; i++)
    {
        res[i] = arr1[i] & arr2[i];
    }
}


int main()
{
    int x[2];
    x[0] = 0;
    x[1]=1;
    int y[2];
    y[0] = 1;
    y[1] = 0;
    int res[2];
    land(x, y, res, 2);
    //printf("%i", x[1]);
    return 0;
}
