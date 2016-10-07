#include "Card.h"

class Hand{
public:
    Hand();
    ~Hand();
    int bet;
    int inGame;
    int inDistribution;
    int purse;
    Card* card[2];
    int ID;
};
