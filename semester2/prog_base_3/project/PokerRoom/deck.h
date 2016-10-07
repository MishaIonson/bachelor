#ifndef DECK_H
#define DECK_H
#include "card.h"
class Deck{
	private:
		Card card[64];
		int pos;
		
	public:
		void putRandom();
		Card getCard();
	
};
#endif