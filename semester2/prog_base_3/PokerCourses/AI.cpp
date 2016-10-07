#include "AI.h"

//  CHECKING THE COMBINATIONS

int AI::findHighHand(Card* card[2])
{
    if (card[0]->getValueIdentifier() > card[1]->getValueIdentifier())
        return card[0]->getValueIdentifier();
    else
        return card[1]->getValueIdentifier();
}

int AI::findPair(int cards[13])
{
    int answer = -1;
    for (int i = 0; i < 13; i++)
        if (cards[i] == 2)
            answer = i;
    return answer;
}
int AI::findTwoPairs(int cards[13])
{
    int answer = -1;
    bool oneFound = false;
    bool twoFound = false;
    for (int i = 0; i < 13; i++)
    {
        if (cards[i] == 2)
        {
            if (!oneFound)
            {
                answer = i;
                oneFound = true;
            }
            else
            {
                if (answer < i)
                    answer = i;
                twoFound = true;
            }
        }
    }

    if (!twoFound)
        answer = -1;

    return answer;
}
int AI::findSet(int cards[13])
{
    int answer = -1;
    for (int i = 0; i < 13; i++)
        if (cards[i] == 3)
            answer = i;
    return answer;
}
int AI::findStraight(int cards[13])
{
    int counter= 0;
    int answer = -1;

    for (int i = 0; i < 13; i++)
    {
        if (cards[i]>0)
            counter++;
        else
        {
            if (counter >= 5)
                answer = i-1;
            counter = 0;
        }
    }
    return answer;
}

int AI::findFlush(Card* card[5], Card* onHand1, Card* onHand2)
{
    int answer = -1;
    int color[4];
    for (int i = 0; i < 4; i++)
        color[i] = 0;

    for (int i = 0; i < 5; i++)
        color[card[i]->getColorIdentifier()]++;

    color[onHand1->getColorIdentifier()]++;
    color[onHand2->getColorIdentifier()]++;

    for (int i = 0; i < 4; i++)
    {
        if (color[i] >= 5)
        {
            if ((onHand1->getColorIdentifier() == i) && (onHand2->getColorIdentifier() == i) && (onHand1->getValueIdentifier() > onHand2->getValueIdentifier()))
                answer = onHand1->getValueIdentifier();
            else if ((onHand1->getColorIdentifier() == i) && (onHand2->getColorIdentifier() == i) && (onHand1->getValueIdentifier() < onHand2->getValueIdentifier()))
                answer = onHand2->getValueIdentifier();
            else if ((onHand1->getColorIdentifier() == i) && (onHand2->getColorIdentifier() != i))
                answer = onHand1->getValueIdentifier();
            else //if ((onHand1->getColorIdentifier() != i) && (onHand2->getColorIdentifier() == i))
                answer = onHand2->getValueIdentifier();
        }
    }

    return answer;




}
int AI::findFullHouse(int cards[13])
{
    int answer = -1;
    bool foundPair = false;
    bool foundSet = false;
    for (int i = 0; i < 13; i++)
    {
        if (cards[i] == 2)
        {
            foundPair = true;
            if (answer < i)
                answer = i;
        }
        if (cards[i] == 3)
        {
            foundSet = true;
            if (answer < i)
                answer = i;
        }
    }

    if (!((foundPair) && (foundSet)))
        answer = -1;

    return answer;
}

int AI::findFourOfAKind(int cards[13])
{
    int answer = -1;
    for (int i = 0; i < 13; i++)
        if (cards[i] == 4)
        {
            answer = i;
            break;
        }

    return answer;
}
