#include "player.h"

		Player::Player(short int placeId_in, int cash_in)
		{
			this.placeId = placeId_in;
			this.cash = cash_in;
			this.moneyInGame = 0;
			this.moneyThisRound = 0;
			this.card[0] = new Card();
			this.card[1] = new Card();
		}
		
		
		short int Player::getPlaceId()
		{
			return Player::placeId;
		}
		
		void Player::setPlaceId(int id)
		{
			Player::placeId = id;
		}
		
		int Player::getCash()
		{
			return cash;
		}
		
		void Player::setCash(int cashIn)
		{
			this.cash = cashIn;
		}
		
		int Player::getMoneyInGame()
		{
			return moneyInGame;
		}
		
		void Player::setMoneyInGame(int money)
		{
			Player::moneyInGame = money;
		}
		
		int Player::getMoneyThisRound()
		{
			return moneyThisRound;
		}
		
		void Player::setMoneyThisRound(int money)
		{
			Player::moneyThisRound = money;
		}
		