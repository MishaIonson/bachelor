#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int i,j;
int new_mat[4][4];
void fillRand(int mat[4][4])
{
    int k;
    for (i = 0; i<4; i++)
    {
        for (j=0; j<4; j++)
        {
            mat[i][j] = rand() % 1999 - 999;
        }
    }
}
void rotateCCW90(int mat[4][4])
{
    for (i = 0; i<4; i++)
    {
        for (j=0; j<4; j++)
        {
            new_mat[i][j] = mat[j][3-i];
        }
    }

    // answer
    for (i = 0; i<4; i++)
    {
        for (j=0; j<4; j++)
        {
            mat[i][j] = new_mat[i][j];
        }
    }

}
void flipH(int mat[4][4])
{
    int j2;
    for (i = 0; i<4; i++)
    {
        for (j=0, j2=3; j<4, j2>=0; j++, j2--)
        {
            new_mat[i][j] = mat[i][j2];
        }
    }

        // answer
    for (i = 0; i<4; i++)
    {
        for (j=0; j<4; j++)
        {
            mat[i][j] = new_mat[i][j];
        }
    }
}
void transposSide(int mat[4][4])
{
    int i2,j2;
    for (i = 0; i<4; i++)
    {
        for (j=0; j<4; j++)
        {
            new_mat[i][j] = mat[j][i];
        }
    }

    for (i = 0, i2=3; i<4, i2>=0; i++, i2--)
    {
        for (j=0, j2=3; j<4, j2>=0; j++, j2--)
        {
            mat[i][j] = new_mat[i2][j2];
        }
    }
    // mat is answer
}
