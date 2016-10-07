#ifndef PLAYER_H
#define PLAYER_H

class Player
{
	private:
		short int placeId; // 1 - 5
		int cash; // money, he has on table now
		Card card[2];
		int moneyInGame; // money, given not in last betting round_error
		int moneyThisRound; // money, given in this betting round
	public:
		Player(short int placeId_in, int cash_in, Card card1, Card card2);
		short int getPlaceId();
		void setPlaceId(int id);
		int getCash();
		void setCash(int cashIn);
		int getMoneyInGame();
		void setMoneyInGame(int money);
		int getMoneyThisRound();
		void setMoneyThisRound(int money);
		void drawOnScreen();
};

#endif