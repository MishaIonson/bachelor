#include <stdio.h>
#include <stdlib.h>
#include "string.h"

char *ns_convert(char number[100], unsigned int sourceBase, unsigned int destBase)
{
    int i;
    // checking the wrightness of number
    short int check_the_wright=0;
    for (i=0; i<strlen(number); i++)
    {
        if (((int)number[i]>=65) && ((int)number[i]<=90))
        {
            if ((number[i]!='.') && (((int)number[i]) - 55>=sourceBase))
            {
                check_the_wright=1;
            }
        }
        else if (((int) number >=48) && ((int) number <=57))
        {
            if ((number[i]!='.') && (((int)number[i]) - 48>=sourceBase))
            {
                check_the_wright=1;
            }
        }

    }
    if (check_the_wright==1)
    {
        return("\0");
    }
    //
    char num[strlen(number)+1];

    for (i=0; i<strlen(number); i++)
    {
        num[i]=number[i];
    }
    num[strlen(number)]='\0';
    // здесь учитывается то, что важно лишь количество знаков до точки, т.к. это перевод целой части
    int degree=1;
    char stop_multiply='f';
    for (i=1; i<strlen(number); i++)
    {
        if (num[i]=='.')
        {
            stop_multiply='t';
        }
        if (stop_multiply=='f')
        {
            degree*=sourceBase;
        }
    }
    //


    i=0;
    int k;
    int numeralTEN=0;
    int sum=0;
    // translate to (10)
    while((num[i]!='.') && (i<strlen(number)))
    {
        if ((num[i]!='0')&& (num[i]!='1')&& (num[i]!='2')&& (num[i]!='3')&& (num[i]!='4')&& (num[i]!='5')&& (num[i]!='6')&& (num[i]!='7')&& (num[i]!='8')&& (num[i]!='9'))
        {
            k=0;
            while(k+65!=(int)num[i])
            {
                k++;
            }
            numeralTEN=k+10;
        }
        else
        {
            if (((int)num[i] >=65) && ( (int) num[i]<=90))
            {
                numeralTEN=(int)num[i] - 55;
            }
            else if (((int)num[i] >=48) && ( (int) num[i]<=57))
            {
                numeralTEN = (int) num[i] - 48;
            }

        }
        sum+=numeralTEN*degree;

        degree/=sourceBase;
        i++;
    }
    // sum - answer of translating
    int residue;
    int tip; // the integer part
    i=0;
    k=0;
    // to know the size of int_part_answer[] -------
    tip=sum;
    while (tip>=destBase)
    {
        tip/=destBase;
        k++;
    }
    char int_part_answer[k+1];// 1 more for the last tip
    //------
    residue=sum%destBase;
    tip=sum/destBase;
    if ((residue>=0) && (residue<=9))
    {
        int_part_answer[i]=(char)residue+48;
    }
    else if ((residue>=10) && (residue<=35))
    {
        int_part_answer[i]=(char)residue+55;
    }


    while(tip>=destBase)
    {
        residue=tip%destBase;
        tip/=destBase;
        i++;
        if ((residue>=0) && (residue<=9))
        {
            int_part_answer[i]=(char)residue+48;
        }
        else if ((residue>=10) && (residue<=35))
        {
            int_part_answer[i]=(char)residue+55;
        }
    }
    i++;
    if ((tip>=0) && (tip<=9))
    {
        int_part_answer[i]=(char)tip+48;
    }
    else if ((tip>=10) && (tip<=35))
    {
        int_part_answer[i]=(char)tip+55;
    }
    char answer_int[i+2];
    int to_remember=i+1;
    for (k=0, degree=i; k<=i, degree>=0; k++, degree--)
    {
        answer_int[k]=int_part_answer[degree];
    }
    answer_int[i+1]='\0';


    // END OF TRANSLATING THE INTEGER PART

    // translating the float part

    // to (10)
    i=0;
    k=0;
    while(num[i]!='.')
    {
       i++;
    }
    i++;
    k=i;
    float degree2=(float) 1/sourceBase;
    float sum2=0;
    float part=0;
    while (strlen(number)>k)
    {
        if (((int)num[k] >=65) && ( (int) num[k]<=90))
        {
            part=(float)((int)num[k] - 55)*degree2;
        }
        else if (((int)num[k] >=48) && ( (int) num[k]<=57))
        {
            part=(float)((int)num[k] - 48)*degree2;
        }

        degree2/=(float)sourceBase;
        sum2+=part;
        k++;
    }
    // to destBase numeral system
    int int_part=0;
    float float_part=0.0;
    char answer_float[12];
    for (k=0; k<12; k++)
    {
        sum2=(float) sum2*destBase;
        int_part = sum2;
        sum2-=int_part;

        if ((int_part>=0) && (int_part<=9))
        {
            answer_float[k]=(char)int_part + 48;
        }
        else if ((int_part>=10) && (int_part<=35))
        {
            answer_float[k]=(char)int_part + 55;
        }
    }
    // end of translating the float part
    char the_answer[to_remember+14];
    the_answer[to_remember+13]='\0';
    i=0;
    while(i<to_remember)
    {
        the_answer[i]=answer_int[i];
        i++;
    }
    k=i;
    i=0;
    the_answer[k]='.';
    while(i<12)
    {
        k++;
        the_answer[k]=answer_float[i];
        i++;
    }
    strcpy(number, the_answer);
    return(number);
}
 int main()
 {
    char x[100];
    strcpy(x, "A");
    printf("%s", ns_convert(x, 12, 10));
    return 0;
 }
