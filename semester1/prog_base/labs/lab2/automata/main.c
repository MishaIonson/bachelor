#include <stdio.h>
#include <stdlib.h>
#include <math.h>
enum commands {Pop=-10, Push, Continue, Repeat, Break};

struct move_info
{
    int command;
    int what_to_push;
    int state;
};
int run(int moves[], int movesLen, int res[], int resLen)
{
    struct move_info what_to_do[4][4];
    int i,j;
    what_to_do[0][0].command = Push;
    what_to_do[0][0].what_to_push=1;
    what_to_do[0][0].state = 1;

    what_to_do[0][1].command = Repeat;
    what_to_do[0][1].state = 1;

    what_to_do[0][2].command = Push;
    what_to_do[0][2].what_to_push = 8;
    what_to_do[0][2].state = 0;

    what_to_do[0][3].command = Break;

    what_to_do[1][0].command = Pop;
    what_to_do[1][0].state = 3;

    what_to_do[1][1].command = Push;
    what_to_do[1][1].what_to_push = 2;
    what_to_do[1][1].state = 2;

    what_to_do[1][2].command = Break;

    what_to_do[1][3].command = Push;
    what_to_do[1][3].what_to_push = 5;
    what_to_do[1][3].state = 1;

    what_to_do[2][0].command = Push;
    what_to_do[2][0].what_to_push = 6;
    what_to_do[2][0].state = 2;

    what_to_do[2][1].command = Continue;
    what_to_do[2][1].state = 1;

    what_to_do[2][2].command = Push;
    what_to_do[2][2].what_to_push = 3;
    what_to_do[2][2].state = 3;

    what_to_do[2][3].command = Pop;
    what_to_do[2][3].state = 0;

    what_to_do[3][0].command = Break;
    what_to_do[3][2].command = Break;

    what_to_do[3][1].command = Push;
    what_to_do[3][1].what_to_push = 7;
    what_to_do[3][1].state = 3;

    what_to_do[3][3].command = Push;
    what_to_do[3][3].what_to_push = 4;
    what_to_do[3][3].state = 0;


    for (i=0; i<resLen; i++)
    {
        res[i]=0;
    }
    // just put some nums
    //
    int state_now=0;
    int pos_now=0;
    int finish=0; // bool
    for (i=0; i<movesLen; i++)
    {
        if (returner(moves[i])!=NAN)
        {
            switch(what_to_do[state_now][returner(moves[i])].command)
            {
                case Push:
                {
                    res[pos_now] = what_to_do[state_now][returner(moves[i])].what_to_push;
                    state_now = what_to_do[state_now][returner(moves[i])].state;
                    pos_now++;
                    break;
                }
                case Pop:
                {
                    if (pos_now!=0)
                    {
                        res[pos_now]=0;
                        pos_now--;
                    }
                    else
                        finish = 1; // true
                    break;
                }
                case Continue:
                {
                    state_now = what_to_do[state_now][returner(moves[i])].state;
                    break;
                }
                case Repeat:
                {
                    state_now=what_to_do[state_now][returner(moves[i])].state;
                    i--; // yeah, yeah, yeah... just like bad coder
                    break;
                }
                case Break:
                {
                    finish = 1;
                    break;
                }
            }
        }
        else
            finish = 1;

        //
        if (finish==1)
        {
            break;
        }
    }

    i=resLen-1;
    int answer=0;
    while((res[i]==0) && (i>=0))
    {
        answer++;
        i--;
    }
    for (i=0;i<resLen; i++)
    {
        printf("%i ", res[i]);
    }
    return answer;
}
int returner(int x)
{
    if (x==10)
        return 0;
    else if (x==14)
        return 1;
    else if (x==19)
        return 2;
    else if (x==109)
        return 3;
    else
        return NAN;
}
int main()
{
    int res[2];
    int i;
    int rl =3;
    int x[2];
    x[0]=10;
    x[1]=14;
    x[2]=100;
    printf("In: ");
    for (i=0;i<3; i++)
    {
        printf("%i ", x[i]);

    }
    printf("\n");
    int xl=2;
    printf("\nAnswer:%i", run(x,xl,res,rl));
    return 0;
}
