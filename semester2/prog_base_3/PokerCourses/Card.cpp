#include "card.h"

Card::Card()
{
    this->posX = 200;
    this->posY = 200;
    this->width = 50;
    this->height = 50;
    this->visible = true;
}
bool Card::isClicked(int x, int y)
{
    if ((this->posX < x) && (this->posX + this->width >= x) && (this->posY + this->height > y) && (this->posY < y))
        return true;

    return false;
}
short int Card::getValueIdentifier()
{
	return valueIdentifier;
}
std::string Card::getImagePath()
{
	return imagePath;
}
void Card::setValueIdentifier(short int valueInput)
{
    if ((valueInput > 15) || (valueInput < 0))
        return;
	valueIdentifier = valueInput;
}
void Card::setImagePath(std::string pathInput)
{
	imagePath = pathInput;
}

short int Card::getColorIdentifier()
{
	return colorIdentifier;
}

void Card::setColorIdentifier(short int id)
{
    if ((id > 4) || (id < 0))
        return;
	colorIdentifier = id;
}

void Card::setTexture()
{
    this->texture.loadFromFile("img/CardFaces.png");
    this->sprite.setTexture(this->texture);
    this->sprite.setTextureRect(sf::IntRect((float)1183/13 * (this->valueIdentifier), (float)512/4 * (this->colorIdentifier), (float)1183/13, (float)512/4 ));
}

