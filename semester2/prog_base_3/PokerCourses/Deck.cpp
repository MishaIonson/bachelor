#include "Deck.h"
Deck::Deck()
{
	this->pos = 0;
	int colorID = 0;
	int valueID = 0;
	for (int  i = 0; i < 52; i++)
	{
		this->card[i].setColorIdentifier(colorID);
		this->card[i].setValueIdentifier(valueID);
		card[i].visible = false;

		colorID++;

		if (colorID > 3)
		{
			colorID = 0;
			valueID++;
		}
	}
}

void Deck::putRandom()
{
    srand(std::time(0));
    this->pos = 0;
	Card cardSwipe;
	int id1, id2;
	for (int i = 0; i < 100; i++)
	{
		id1 = rand() % 52;
		id2 = rand() % 52;
		cardSwipe = this->card[id1];
		this->card[id1] = this->card[id2];
		this->card[id2] = cardSwipe;
	}
}

Card Deck::getCard()
{
	pos++;
	return card[pos-1];
}
