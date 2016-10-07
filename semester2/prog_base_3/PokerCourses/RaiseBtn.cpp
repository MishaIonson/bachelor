#include "RaiseBtn.h"
#include "Consts.h"

RaiseBtn::RaiseBtn()
{
    this->height = 40;
    this->width = 60;
    this->posX = 60;
    this->posY = SCREEN_HEIGHT - this->height;
    this->texture.loadFromFile("img/raiseBTN.png");
    this->sprite.setTexture(this->texture);
    this->sprite.setPosition(posX, posY);
}

bool RaiseBtn::isPressed(float x, float y)
{
    if ((x > this->posX) && ( x < this->posX + this->width) && (y > this->posY) && (y < this->posY + this->height))
        return true;
    else
        return false;
}

