struct Snake
{
    char way;// LRFB
    int length;
    int ex_positions[80*25][2];
    int nowX;
    int nowY;
    int speed;
    char name[100];
};
