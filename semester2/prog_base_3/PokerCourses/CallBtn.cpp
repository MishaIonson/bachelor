#include "CallBtn.h"
#include "Consts.h"

CallBtn::CallBtn()
{
    this->height = 40;
    this->width = 60;
    this->posX = 0;
    this->posY = SCREEN_HEIGHT - this->height;
    this->texture.loadFromFile("img/callBTN.png");
    this->sprite.setTexture(this->texture);
    this->sprite.setPosition(posX, posY);
}

void CallBtn::setPosition(float x, float y)
{
    this->posX = x;
    this->posY = y;
    this->sprite.setPosition(posX, posY);
}

bool CallBtn::isPressed(float x, float y)
{
    if ((x > this->posX) && ( x < this->posX + this->width) && (y > this->posY) && (y < this->posY + this->height))
        return true;
    else
        return false;
}

void CallBtn::called(int playerID, int* bet, int* playersPurse)
{
    int maximal = bet[playerID];
    for (int i = 0; i < 5; i++)
        if (maximal < bet[i])
            maximal = bet[i];

    int k = maximal - bet[playerID];
    playersPurse -= k;
    bet[playerID] = maximal;
}
