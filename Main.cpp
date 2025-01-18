#include<iostream>
#include"Card.h"
#include"List.h"
#include"Stack.h"
#include"Command.h"
#include"Game.h"

using namespace std;
int main()
{
	HANDLE cConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(cConsole, 14);
	cout << "Welcome to Solitaire. Have Fun!" << endl << endl;
	SetConsoleTextAttribute(cConsole, 0x0F);
	Game app;
	return 0;

}

