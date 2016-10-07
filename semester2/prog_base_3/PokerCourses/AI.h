#include "Card.h"
class AI
{
public:
    int findPair(int cards[13]);
    int findTwoPairs(int cards[13]);
    int findSet(int cards[13]);
    int findFullHouse(int cards[13]);
    int findHighHand(Card* card[2]);
    int findStraight(int cards[13]);
    int findFourOfAKind(int cards[13]);
    int findFlush(Card* card[5], Card* onHand1, Card* onHand2);
};
