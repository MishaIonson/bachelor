#include "card.h"

Card::Card()
{
	
}
short int Card::getValueIdentifier()
{
	return valueIdentifier;
}
String Card::getImagePath()
{
	return imagePath;
}
void Card::setValueIdentifier(short int valueInput)
{
	valueIdentifier = valueInput;
}
void Card::setImagePath(String pathInput)
{
	imagePath = pathInput;
}

short int Card::getColorIdentifier()
{
	return colorIdentifier;
}

void Card::setColorIdentifier(short int id)
{
	colorIdentifier = id;
}