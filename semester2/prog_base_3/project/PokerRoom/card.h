#ifndef CARD_H
#define CARD_H

class Card
{
	private:
		short int valueIdentifier;
		short int colorIdentifier;
		String imagePath;
	public:
		short int getValueIdentifier();
		String getImagePath();
		void setValueIdentifier(short int valueInput);
		void setImagePath(String pathInput);
		void drawOnScreen();
		short int getColorIdentifier();
		void setColorIdentifier(short int id);
};

#endif