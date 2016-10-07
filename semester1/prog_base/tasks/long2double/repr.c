#include <stdio.h>
#include <stdlib.h>
#include "math.h"
/*double long2double(long long num)
{
    int num_in_bit[64];
    int i;
    for (i=0; i<64; i++)
    num_in_bit[i] = 0;

    if (num>=0)
        num_in_bit[0] = 0;
    if (num<0)
    {
        num_in_bit[0] = 1;
        num*=-1;
        num--;
    }
    i=1;
    while (num!=0)
    {
        if (num_in_bit[0] == 0)
        {
            num_in_bit[i] = num%2;
        }
        else
        {
           if (num%2 == 1)
           num_in_bit[i]=0;

           if (num%2 == 0)
           num_in_bit[i]=1;
        }
        num/=2;
        i++;
    }
    int int_part=0;
    double float_part=0.0;
    for (i = 11; i>=1; i--)
    {
        int_part += num_in_bit[i] * pow(2, i-1);
    }
    printf("%i\n", int_part);
    int k = -1;
    for ( i = 1; i<=52; i++)
    {
        float_part += (double) num_in_bit[i] * pow(2,k);
        printf("float_part: %f,  %i\n",float_part, num_in_bit[i]);
        k--;
    }
    double answer;
    if (num_in_bit[0]==1)
        answer*=-1;



    // ok nums
    if ((int_part>0) && (int_part<2047))
    {
        answer = pow(2,int_part-1023)*(1+float_part);
        if (num_in_bit[0] == 1)
        answer*=-1;
    }
    if ((int_part==0) && (float_part!=0))
    {
        answer = pow(2,-1022)*float_part;
        if (num_in_bit[0] == 1)
        answer*=-1;
    }

    //some consts
    if ((int_part==2047) && (float_part!=0))
        answer =NAN;
    if ((int_part==2047) && (float_part==0) && (num_in_bit[0] == 0))
        answer = INFINITY;
    if ((int_part==2047) && (float_part==0) &&(num_in_bit[0] == 1))
        answer = -INFINITY;
    if ((int_part==0) && (float_part==0) && (num_in_bit[0] == 0))
    {
        answer = +0.0;
    }
    if ((int_part==0) && (float_part==0) && (num_in_bit[0] == 1))
    {
        answer = -0.0;
    }


    return answer;
}*/

double long2double(long long num)
{
	int num_in_bit[64];
	int i;
	for (i = 0; i<64; i++)
		num_in_bit[i] = 0;

	if (num>0)
		num_in_bit[0] = 0;
	if (num<0)
	{
		num_in_bit[0] = 1;
		num *= -1;
		num--;
	}
	if (num == 0)
		return 0;
	i = 1;
	while (num != 0)
	{
		if (num_in_bit[0] == 0)
		{
			num_in_bit[i] = num % 2;
		}
		else
		{
			if (num % 2 == 1)
				num_in_bit[i] = 0;

			if (num % 2 == 0)
				num_in_bit[i] = 1;
		}
		num /= 2;
		i++;
	}


	int int_part = 0;
	double float_part = 0.0;
	for (i =11; i >= 1; i--)
	{

		int_part +=num_in_bit[64-i] * pow(2, i - 1);
	}
	int k = -1;
	for (i = 52; i >= 1; i--)
	{
		float_part += num_in_bit[i] * pow(2, k);
		k--;
	}
	double answer=1;
	if (num_in_bit[0] == 1)
		answer *= -1;

	// ok nums
	if ((int_part>0) && (int_part<2047))
	{
		answer = pow(2, int_part - 1023)*(1 + float_part);
		if (num_in_bit[0] == 1)
			answer *= -1;
	}
	if ((int_part==0) && (float_part != 0))
	{
		answer = pow(2, -1022)*float_part;
		if (num_in_bit[0] == 1)
			answer *= -1;
	}

	//some consts
	if ((int_part == 2047) && (float_part != 0))
		answer = NAN;
	if ((int_part == 2047) && (float_part == 0) && (num_in_bit[0] == 0))
		answer = INFINITY;
	if ((int_part == 2047) && (float_part == 0) && (num_in_bit[0] == 1))
		answer = -INFINITY;
	if ((int_part == 0) && (float_part == 0) && (num_in_bit[0] == 0))
	{
		answer = +0.0;
	}
	if ((int_part == 0) && (float_part == 0) && (num_in_bit[0] == 1))
	{
		answer = -0.0;
	}

	return answer;
}
