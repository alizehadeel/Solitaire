#include "Game.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

Game::Game()
{
	cout << "Game Rules:\n";
	cout << "Use s to draw card from the stockpile.\nUse the format- m src dest numOfCards- to move between tableaus and foundations.\nPress z to undo.\nPress Q to quit the game.\n\n";
	setupNewGame();
	printGameState();
	play();
}
void Game::setupNewGame()
{
	// Initialize a deck of 52 cards
	Card* deck=new Card[52];
	int index = 0;

	for (char s : {'H', 'S', 'C', 'D'})
		for (int r = 1; r <= 13; r++)
		{
			deck[index] = Card(s, r);
			index++;
		}

	//Shuffle the deck
	srand(time(nullptr));//setting up the random number generator
	for (int i = 0; i < 52; i++)//iteration is looking to shuffle the card at position i
	{
		int r = i + (rand() % (52 - i)); //ensures that the random number falls within a valid range and not shuffling cards that have already been shuffled.
		swap(deck[i], deck[r]);
	}

	//Distribute the deck to tableau columns
	int deckIndex = 0;
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j <= i; j++)
		{
			Card* c = new Card(deck[deckIndex]);//this isnt pointers so dont need to manually deep copy
			tableau[i].addCard(c);
			deckIndex++;
		}
		tableau[i].end().getCard()->flip();
	}
	for (; deckIndex < 52; deckIndex++)
	{
		Card* c = new Card(deck[deckIndex]);
		stockpile.pushC(c);
	}
}
void Game::play()
{
	char input[15];
	bool gameOver = false;
	while (!gameOver)
	{
		gameOver = isGameOver();
		cout << "Enter your move: ";
		cin.getline(input, 14);

		if (input[0]=='Q' || input[0] == 'q')
		{
			gameOver = true;
			cout << "Game ended by user. \n";
		}
		else if(!gameOver)
			processMove(input);
	}
	cout << "Game Over!";
}
void Game::printGameState()
{

		HANDLE gConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(gConsole, 0x0A);
		cout << "Stock\t\tWastepile\t\t\tFoundation H\t\tFoundation S\t\tFoundation D\t\tFoundation C" << endl;
		HANDLE wConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(wConsole, 0x0F);

		stockpile.peekC()->print();
		cout << "\t\t";
		wastepile.peekC()->print();
		cout << "\t\t\t\t";
		foundation[0].peekC()->print();
		cout << "\t\t\t";
		foundation[1].peekC()->print();
		cout << "\t\t\t";
		foundation[2].peekC()->print();
		cout << "\t\t\t";
		foundation[3].peekC()->print();
		cout << endl;

		cout << "(" << stockpile.getSize() << " cards)\t" << "(" << wastepile.getSize() << " cards)\t\t\t" << "(" << foundation[0].getSize() << " cards)\t\t(" << foundation[1].getSize() << " cards)\t\t(" << foundation[2].getSize() << " cards)\t\t(" << foundation[3].getSize() << " cards)\n\n";

		SetConsoleTextAttribute(gConsole, 0x0A);
		cout << "Column 1\tColumn 2\tColumn 3\tColumn 4\tColumn 5\tColumn 6\tColumn 7" << endl;
		SetConsoleTextAttribute(wConsole, 0x0F);

		int i = 0;
		bool endOfTableaus = false;
		List::Iterator i1(tableau[0].begin());
		List::Iterator i2(tableau[1].begin());
		List::Iterator i3(tableau[2].begin());
		List::Iterator i4(tableau[3].begin());
		List::Iterator i5(tableau[4].begin());
		List::Iterator i6(tableau[5].begin());
		List::Iterator i7(tableau[6].begin());
		while (!endOfTableaus)
		{
			if (*i1 != nullptr)
			{
				i1.getCard()->print();
				cout << "\t\t";
				++i1;
			}
			else
				cout << "\t\t";
			if (*i2 != nullptr)
			{
				i2.getCard()->print();
				cout << "\t\t";
				++i2;
			}
			else
				cout << "\t\t";
			if (*i3 != nullptr)
			{
				i3.getCard()->print();
				cout << "\t\t";
				++i3;
			}
			else
				cout << "\t\t";
			if (*i4 != nullptr)
			{
				i4.getCard()->print();
				cout << "\t\t";
				++i4;
			}
			else
				cout << "\t\t";
			if (*i5 != nullptr)
			{
				i5.getCard()->print();
				cout << "\t\t";
				++i5;
			}
			else
				cout << "\t\t";
			if (*i6 != nullptr)
			{
				i6.getCard()->print();
				cout << "\t\t";
				++i6;
			}
			else
				cout << "\t\t";
			if (*i7 != nullptr)
			{
				i7.getCard()->print();
				cout << "\t\t";
				++i7;
			}
			else
				cout << "\t\t";
			i++;
			cout << endl;
			if (*i7 == nullptr && *i6 == nullptr && *i5 == nullptr && *i4 == nullptr && *i3 == nullptr && *i2 == nullptr && *i1 == nullptr)
			{
				endOfTableaus = true;
			}
		}
		cout << endl;
}
void Game::processMove(const string& input)
{
	bool validMove = true;
	if (input[0] == 's' || input[0] == 'S')
	{
		if (stockpile.getSize() > 0)
		{
			Command* com = new Command(input[0], 0, 0, 1);
			wastepile.pushN(stockpile.popN());
			wastepile.peekC()->flip();
			undoStack.pushC(com);
		}
		else
		{
			while (wastepile.getSize() > 0)
			{
				wastepile.peekC()->flip();
				stockpile.pushN(wastepile.popN());
				
			}
			Command* com = new Command(input[0], 0, 0, 1);
		}
	}
	else if (input[0] == 'm' || input[0] == 'M')
	{
		if ((input[2] == 'c' || input[2] == 'C') && (input[5] == 'C' || input[5] == 'c'))
		{
			int s = input[3] - 49;
			int d = input[6] - 49;
			int n = input[8] - 48;
			Command* com = new Command(input[0], s, d, n);

			List::Iterator iT(tableau[s].end());
			List::Iterator iT2(tableau[d].end());
			while (n>1)
			{
				iT--;
				n--;
			}
			n = input[8] - 48;

			if (iT2 == nullptr)
			{
				if (iT.getCard()->getRank() == 13)
				{
					List::Iterator iS(tableau[s].extractSublist(n));
					tableau[d].addSubList(*iS, n);
					if (tableau[s].end().getCard() != nullptr && !tableau[s].end().getCard()->isFaceUp())
					{
						tableau[s].end().getCard()->flip();
					}
					Command* com = new Command(input[0], s, d, n);
					undoStack.pushC(com);
				}
				else
					validMove = false;
			}
			else if ((iT.getCard()->getRank() + 1 == iT2.getCard()->getRank()) && ((iT.getCard()->isColourRed() && !iT2.getCard()->isColourRed()) || (!iT.getCard()->isColourRed() && iT2.getCard()->isColourRed())))
			{
				List::Iterator iS(tableau[s].extractSublist(n));
				tableau[d].addSubList(*iS, n);
				if (tableau[s].end().getCard() != nullptr && !tableau[s].end().getCard()->isFaceUp())
				{
					tableau[s].end().getCard()->flip();
				}
				Command* com = new Command(input[0], s, d, n);
				undoStack.pushC(com);
			}
			else
				validMove = false;
		}
		else if ((input[2] == 'c' || input[2] == 'C') && (input[5] == 'F' || input[5] == 'f'))
		{
			int s = input[3] - 49;
			int d = input[6] - 49 + 7;//differentiating foundation from tableaus in command class
			int n = input[8] - 48;

			List::Iterator iT(tableau[s].end());
			if (foundation[d-7].peekC()==nullptr && iT.getCard()->getRank()==1)
			{
				if ((iT.getCard()->getSuit() == 'H' && d == 7) || (iT.getCard()->getSuit() == 'S' && d == 8) || (iT.getCard()->getSuit() == 'D' && d == 9) || (iT.getCard()->getSuit() == 'C' && d == 10))
				{
					foundation[d - 7].pushC(tableau[s].removeCard());
					if (tableau[s].end().getCard() != nullptr && !tableau[s].end().getCard()->isFaceUp())
					{
						tableau[s].end().getCard()->flip();
					}
					Command* com = new Command(input[0], s, d, n);
					undoStack.pushC(com);
				}
				else
					validMove = false;

			}
			else if(foundation[d - 7].peekC() != nullptr)
			{
				if (iT.getCard()->getRank() - 1 == foundation[d - 7].peekC()->getRank())
				{
					if ((iT.getCard()->getSuit() == 'H' && d == 7) || (iT.getCard()->getSuit() == 'S' && d == 8) || (iT.getCard()->getSuit() == 'D' && d == 9) || (iT.getCard()->getSuit() == 'C' && d == 10))
					{
						foundation[d - 7].pushC(tableau[s].removeCard());
						if (tableau[s].end().getCard() != nullptr && !tableau[s].end().getCard()->isFaceUp())
						{
							tableau[s].end().getCard()->flip();
						}
						Command* com = new Command(input[0], s, d, n);
						undoStack.pushC(com);
					}
					else
						validMove = false;
				}
				else
					validMove = false;
			}
			else
			{
				validMove = false;
			}
		}
		else if (input[2] == 'w' || input[2] == 'W')
		{
			int s = input[2] - 119 + 11;//code for wastepile
			int d = input[5] - 49;
			int n = input[7] - 48;

			List::Iterator iT2(tableau[d].end());
			if (iT2==nullptr)
			{
				if (wastepile.peekC()->getRank()==13)
				{
					Command* com = new Command(input[0], s, d, n);
					undoStack.pushC(com);
					tableau[d].addCard(wastepile.popC());
				}
				else
					validMove = false;
			}
			else if ((wastepile.peekC()->getRank() + 1 == iT2.getCard()->getRank()) && ((wastepile.peekC()->isColourRed() && !iT2.getCard()->isColourRed()) || (!wastepile.peekC()->isColourRed() && iT2.getCard()->isColourRed())))
			{
				Command* com = new Command(input[0], s, d, n);
				undoStack.pushC(com);
				tableau[d].addCard(wastepile.popC());
			}
			else
				validMove = false;
		}
		else if (input[2] == 'f' || input[2] == 'F')
		{
			int s = input[3] - 49 + 7;//differentiating foundation from tableaus
			int d = input[6] - 49;
			int n = input[8] - 48;

			List::Iterator iT2(tableau[d].end());
			if (iT2 == nullptr)
			{
				if (foundation[s - 7].peekC()->getRank() == 13)
				{
					Command* com = new Command(input[0], s, d, n);
					undoStack.pushC(com);
					tableau[d].addCard(foundation[s - 7].popC());
				}
				else
					validMove = false;
			}
			else if(!foundation[s - 7].isEmpty())
			{
				if ((foundation[s - 7].peekC()->getRank() + 1 == iT2.getCard()->getRank()) && ((foundation[s - 7].peekC()->isColourRed() && !iT2.getCard()->isColourRed()) || (!foundation[s - 7].peekC()->isColourRed() && iT2.getCard()->isColourRed())))
				{
					Command* com = new Command(input[0], s, d, n);
					undoStack.pushC(com);
					tableau[d].addCard(foundation[s - 7].popC());
				}
			}
			else
				validMove = false;

			
		}
	}
	else if (input[0] == 'z' || input[0] == 'Z')
	{
		if (!undoStack.isEmpty())
		{
			undo();
		}
		else
			validMove = false;
	}
	else
		validMove = false;
		if (validMove)
			printGameState();
		else
			cout << "Invalid move, try again!" << endl;


}
void Game::undo()
{
	Command* com = undoStack.popC();
	if (com->getType() == 's')
	{
		if (wastepile.getSize() != 0)
		{
			stockpile.pushN(wastepile.popN());
			stockpile.peekC()->flip();
		}
		else
		{
			while (stockpile.getSize() > 0)
			{
				wastepile.pushN(stockpile.popN());
				wastepile.peekC()->flip();

			}
		}
	}
	if (com->getType() == 'm')
	{
		int s = com->getSource();
		int d = com->getDestination();
		int n = com->getNumCards();
		if ((s >= 0 && s <= 6) && (d>=0 && d <=6))
		{
			List::Iterator iS(tableau[s].end());
			List::Iterator iD(tableau[d].end());
			List::Iterator iT(tableau[d].extractSublist(n));

			if (tableau[s].end() != nullptr)
			{

				if (iS.getCard()->getRank() - 1 == iT.getCard()->getRank() && ((iS.getCard()->isColourRed() && !iT.getCard()->isColourRed()) || (!iS.getCard()->isColourRed() && iT.getCard()->isColourRed())))
					;
				else
					tableau[s].end().getCard()->flip();
				tableau[s].addSubList(*iT, n);
			}

		}
		else if ((s >= 0 && s <= 6) && (d >= 7 && d <= 10))
		{
			List::Iterator i(tableau[s].end());
			if (tableau[s].end() != nullptr)
			{
				if (i.getCard()->getRank() - 1 == foundation[d - 7].peekC()->getRank() && ((i.getCard()->isColourRed() && !foundation[d - 7].peekC()->isColourRed()) || (!i.getCard()->isColourRed() && foundation[d - 7].peekC()->isColourRed())))
					;
				else
					tableau[s].end().getCard()->flip();
			}
			tableau[s].addCard(foundation[d - 7].popC());
		}
		else if ((s >= 7 && s <= 10) && (d >= 0 && d <= 6))
		{
			foundation[s - 7].pushC(tableau[d].removeCard());
		}
		else if (s = 11 && (d >= 0 && d <= 6))
		{
			wastepile.pushC(tableau[d].removeCard());
		}
	}
	
}
bool Game::isGameOver() 
{

	if (isGameWon())	// Check if the game is won (all foundations are complete) 
	{
		cout << "Congratulations! You've won the game!" << endl;
		return true;
	}

	if (noMoreMoves())
	{
		cout << "No more moves left. Game over!" << endl;
		return true;
	}
	return false;
}
bool Game::isGameWon() 
{
	for (int i = 0; i < 4; ++i) {
		if (foundation[i].getSize() != 13) {
			return false;  
		}
	}
	return true;  
}
bool Game::noMoreMoves()
{
	for (int src = 0; src < 7; ++src) //checking for tableau against tableai=u movements
	{
		if (!tableau[src].isEmpty())
		{
			for (int dest = 0; dest < 7; ++dest) 
			{
				if (canMoveTableauToTableau(src, dest)) 
				{
					return false;  
				}
			}
		}
	}
	for (int t = 0; t < 7; ++t) 
	{
        if (!tableau[t].isEmpty() && canMoveToFoundation(tableau[t].end().getCard())) 
		{
            return false; 
        }
    }
	if (!wastepile.isEmpty() || !stockpile.isEmpty())
	{
		return false;
	}
	return true;
	
}
bool Game::canMoveTableauToTableau(int src, int dest)
{
	if (tableau[src].end().getCard()->getRank() + 1 == tableau[dest].end().getCard()->getRank())
		return true;
	else
		return false;
}
bool Game::canMoveToFoundation(Card* card)
{
	for (int i = 0; i < 4; i++)
	{
		if (foundation[i].peekC()->getRank()+1==card->getRank() && foundation[i].peekC()->getSuit() == card->getSuit())
		{
			return true;
		}
	}
	return false;
}
bool Game::canMoveToTableau(Card* card)
{
	for (int i = 0; i < 7; i++)
	{
		if (tableau[i].end().getCard()->getRank() - 1 == card->getRank() && ((tableau[i].end().getCard()->isColourRed() && !card->isColourRed()) || (!tableau[i].end().getCard()->isColourRed() && card->isColourRed())))
			return true;
	}
	return false;
}
