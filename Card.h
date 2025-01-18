#pragma once
#include <windows.h>

class Card
{
private:
	char suit;// h,d,s,c
	int rank;	// 1 to 13 (Ace = 1, Jack = 11, Queen = 12, King = 13)
	bool faceUp;
public:
	Card();
	Card(char s, int r, bool face = false)
	{
		suit = s;
		rank = r;
		faceUp = face;
	}
	void print();
	static void setTextColor(int color);	//general utility function not tied to any object
	void flip() { faceUp = !faceUp; }
	char getSuit() { return suit; }
	int getRank() 
	{
		if (this != nullptr)
			return rank;
		else
			return 0;
	}
	bool isColourRed()
	{
		if (suit == 'C' || suit == 'S')
			return false;
		else return true;
	}
	bool isFaceUp() { return faceUp; }
};
