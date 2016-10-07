#include <stdio.h>
#include <stdlib.h>
#include "string.h"

char exactlySign(int x)
{
    if (x==0)
    {
        return('0');
    }
    if (x==1)
    {
        return('1');
    }
    if (x==2)
    {
        return('2');
    }
    if (x==3)
    {
        return('3');
    }
    if (x==4)
    {
        return('4');
    }
    if (x==5)
    {
        return('5');
    }
    if (x==6)
    {
        return('6');
    }
    if (x==7)
    {
        return('7');
    }
    if (x==8)
    {
        return('8');
    }
    if (x==9)
    {
        return('9');
    }
    if (x==10)
    {
        return('A');
    }
    if (x==11)
    {
        return('B');
    }
    if (x==12)
    {
        return('C');
    }
    if (x==13)
    {
        return('D');
    }
    if (x==14)
    {
        return('E');
    }
    if (x==15)
    {
        return('F');
    }
    if (x==16)
    {
        return('G');
    }
    if (x==17)
    {
        return('H');
    }
    if (x==18)
    {
        return('I');
    }
    if (x==19)
    {
        return('J');
    }
    if (x==20)
    {
        return('K');
    }
    if (x==21)
    {
        return('L');
    }
    if (x==22)
    {
        return('M');
    }
    if (x==23)
    {
        return('N');
    }
    if (x==24)
    {
        return('O');
    }
    if (x==25)
    {
        return('P');
    }
    if (x==26)
    {
        return('Q');
    }
    if (x==27)
    {
        return('R');
    }
    if (x==28)
    {
        return('S');
    }
    if (x==29)
    {
        return('T');
    }
    if (x==30)
    {
        return('U');
    }
    if (x==31)
    {
        return('V');
    }
    if (x==32)
    {
        return('W');
    }
    if (x==33)
    {
        return('X');
    }
    if (x==34)
    {
        return('Y');
    }
    if (x==35)
    {
        return('Z');
    }
}
int exactlyNum(char x[])
{
    if (x=='0')
    {
        return(0);
    }
    if (x=='1')
    {
        return(1);
    }
    if (x=='2')
    {
        return(2);
    }
    if (x=='3')
    {
        return(3);
    }
    if (x=='4')
    {
        return(4);
    }
    if (x=='5')
    {
        return(5);
    }
    if (x=='6')
    {
        return(6);
    }
    if (x=='7')
    {
        return(7);
    }
    if (x=='8')
    {
        return(8);
    }
    if (x=='9')
    {
        return(9);
    }
    if (x=='A')
    {
        return(10);
    }
    if (x=='B')
    {
        return(11);
    }
    if (x=='C')
    {
        return(12);
    }
    if (x=='D')
    {
        return(13);
    }
    if (x=='E')
    {
        return(14);
    }
    if (x=='F')
    {
        return(15);
    }
    if (x=='G')
    {
        return(16);
    }
    if (x=='H')
    {
        return(17);
    }
    if (x=='I')
    {
        return(18);
    }
    if (x=='J')
    {
        return(19);
    }
    if (x=='K')
    {
        return(20);
    }
    if (x=='L')
    {
        return(21);
    }
    if (x=='M')
    {
        return(22);
    }
    if (x=='N')
    {
        return(23);
    }
    if (x=='O')
    {
        return(24);
    }
    if (x=='P')
    {
        return(25);
    }
    if (x=='Q')
    {
        return(26);
    }
    if (x=='R')
    {
        return(27);
    }
    if (x=='S')
    {
        return(28);
    }
    if (x=='T')
    {
        return(29);
    }
    if (x=='U')
    {
        return(30);
    }
    if (x=='V')
    {
        return(31);
    }
    if (x=='W')
    {
        return(32);
    }
    if (x=='X')
    {
        return(33);
    }
    if (x=='Y')
    {
        return(34);
    }
    if (x=='Z')
    {
        return(35);
    }
}
char *ns_convert(char *number, unsigned int sourceBase, unsigned int destBase)
{
    int i;
    // checking the wrightness of number
    short int check_the_wright=0;
    for (i=0; i<strlen(number); i++)
    {
        if ((number[i]!='.') && (exactlyNum(number[i])>=sourceBase))
        {
            check_the_wright=1;
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
    char *code[26];
    code[0]='A';
    code[1]='B';
    code[2]='C';
    code[3]='D';
    code[4]='E';
    code[5]='F';
    code[6]='G';
    code[7]='H';
    code[8]='I';
    code[9]='J';
    code[10]='K';
    code[11]='L';
    code[12]='M';
    code[13]='N';
    code[14]='O';
    code[15]='P';
    code[16]='Q';
    code[17]='R';
    code[18]='S';
    code[19]='T';
    code[20]='U';
    code[21]='V';
    code[22]='W';
    code[23]='X';
    code[24]='Y';
    code[25]='Z';
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
            while(code[k]!=num[i])
            {
                k++;
            }
            numeralTEN=k+10;
        }
        else
        {
            numeralTEN=exactlyNum(num[i]);
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

    int_part_answer[i]=exactlySign(residue);

    while(tip>=destBase)
    {
        residue=tip%destBase;
        tip/=destBase;
        i++;
        int_part_answer[i]=exactlySign(residue);
    }
    i++;
    int_part_answer[i]=exactlySign(tip);
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
        part=(float)exactlyNum(num[k])*degree2;
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
        answer_float[k]=exactlySign(int_part);
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
    return(the_answer);
}


int main()
{
    char *r=ns_convert("11011.101", 2, 16);
}
