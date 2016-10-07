#include "Hand.h"

Hand::Hand()
{
    for (int i = 0; i < 2; i++)
    {
        this->card[i] = new Card();
    }
}
Hand::~Hand()
{
    for (int i = 0; i < 2; i++)
    {
        delete this->card[i];
    }
}
