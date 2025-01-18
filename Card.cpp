#include<iostream>
#include"Card.h"
using namespace std;

Card::Card()
{
    suit = '0';
    rank = 0;
    faceUp = false;
}
void Card::setTextColor(int color) 
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void Card::print()
{
    if(this!=nullptr){
        if (faceUp) {
            if (suit == 'h' || suit == 'd' || suit == 'H' || suit == 'D') {//♥♦
                setTextColor(0x0C);  // Red for hearts and diamonds
            }
            else
            {
                setTextColor(0x0F);  // Black for spades and clubs
            }

            cout << rank << suit;

            /*switch (suit)
            {
            case 'h':
            case 'H':
                cout << char(3);
                break;
            case 'd':
            case 'D':
                cout << char(4);
                break;
            case 's':
            case 'S':
                cout << char(6);
                break;
            case 'c':
            case 'C':
                cout << char(5);
                break;
            default:
                cout<<suit;
            }*/

            // Reset the text color to white (normal)
            setTextColor(0x0F);
        }
        else
            cout << "[ ]";
    }
    else
        cout << "[   ]";

}
