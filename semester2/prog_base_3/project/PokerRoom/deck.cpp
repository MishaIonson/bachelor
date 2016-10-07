#include "deck.h"
#include "stdafx.h"
Deck::Deck()
{
	pos = 0;
	int colorID = 0;
	int valueID = 0;
	for (int  i = 0; valueID < 52; i++)
	{
		card[i] = new Card();
		card[i].setColorIdentifier(colorID);
		card[i].setValueIdentifier(valueID);
		
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
	Card cardSwipe = new Card();
	int id1, id2;
	for (int i = 0; i < 100; i++)
	{
		id1 = rand() % 52;
		id2 = rand() % 52;
		cardSwipe = card[id1];
		card[id1] = card[id2];
		card[id2] = cardSwipe;
	}
}

Card Deck::getCard()
{
	pos++;
	return card[pos-1];
}