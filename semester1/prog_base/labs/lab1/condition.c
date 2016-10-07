#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
int satisfies(int a, int b, int c)
{
    int answer;
    int sum2;
    int modmin;
    int i;
    short int is_degree=1; // 1-false, 0 - true
    if ((a<0) && (b<0) && (c<0))
    {
        if ((a<=b) && (a<=c))
        {
            modmin=abs(a);

            sum2=b+c;
        }

        if ((b<=a) && (b<=c))
        {
            modmin=abs(b);

            sum2=a+c;
        }
        if ((c<=b) && (c<=a))
        {
            modmin=abs(c);

            sum2=b+a;
        }

        //

        for (i=1; i<=modmin; i*=2)
        {
            if (i==modmin)
            is_degree=0;
        }
        //

        if ((sum2<-256) && (!is_degree))
        {
            answer=1; // true
        }
        else
        {
            int mod_sum2=sum2;
            if (sum2<0)
            mod_sum2*=(-1);

            return ((mod_sum2>modmin) && (sum2>-256));

        }
    }

    //
    int abc[3], k[2];
    abc[0]=a;
    abc[1]=b;
    abc[2]=c;

    int that_num[2];
    int num_of_negative=0;
    for (i=0; i<3; i++)
    {
        if (abc[i]<0)
        {
            num_of_negative++;
        }
        if (num_of_negative==1)
        that_num[0]=abc[i];
        if (num_of_negative==2)
        that_num[1]=abc[i];
    }

    if (num_of_negative==1)
    {
         if (that_num[0]>-256)
         answer=1; //true
         else
         answer=0; //false
    }
    if (num_of_negative==2)
    {
        return((that_num[0]+that_num[1])*9>-256);
    }

    //
    int max=a, min=a;
    if ((a>=0) && (b>=0) && (c>=0))
    {
        if (max<b)
        {
            max=b;
        }
        if (max<c)
        max=c;

        if (min>b)
        min=b;
        if (min>c)
        min=c;

        int bool_can=0; // 0 - true, 1 - false
        int index=1;
        long long pow_num=max;
        while(index<min)
        {
            if ((pow_num > INT_MAX) || (pow_num < INT_MIN))
            bool_can=1;

            index++;
            pow_num*=max;
        }
        return(bool_can==0);
    }


    return answer;
}

