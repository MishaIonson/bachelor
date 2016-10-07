public int getWinnerId(Player p1, player p2)
{
	int player1Combination;
	int player2Combination;
	if ((player1Combination == player2Combination) && (player2Combination == 0)
}


/*
LIST OF COMBINATIONS INDEXES:
0 - high cardOnHand
1 - pair
2 - 2 pairs
3 - 3 of 1 kind
4 - straight
5 - flash
6 - 4 of 1 kind
7 - straight flash
8 - royal flash
*/
public int getCombinationPower(Card cardOnHand, Card onTable[])
{
	// @TODO
	int onePair[2];
	int twoPairs[2];
	int threeOfAKind[2];
	int fourOfAKind[2];
	onePair[0] = 0;
	twoPairs[0] = 0;
	threeOfAKind[0] = 0;
	fourOfAKind[0] = 0;
	for (int i = 0; i < onTable.size(); i ++)
	{
		if (cardOnHand.valueIdentifier == onTable[i].valueIdentifier)
		{
			if (pairID1 == -1)
			{
				pairID1 = cardOnHand.valueIdentifier;
			}
		}
	}
}