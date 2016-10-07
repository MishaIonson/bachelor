#include "FoldBtn.h"
#include "Consts.h"

FoldBtn::FoldBtn()
{
    this->height = 40;
    this->width = 60;
    this->posX = 2*60;
    this->posY = SCREEN_HEIGHT - this->height;
    this->texture.loadFromFile("img/foldBTN.png");
    this->sprite.setTexture(this->texture);
    this->sprite.setPosition(posX, posY);
}

bool FoldBtn::isPressed(float x, float y)
{
    if ((x > this->posX) && ( x < this->posX + this->width) && (y > this->posY) && (y < this->posY + this->height))
        return true;
    else
        return false;
}
