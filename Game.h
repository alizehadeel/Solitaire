#include "List.h"
#include "Stack.h"
#include "Command.h"
#include"Card.h"
#include <string>
#include <windows.h>

class Game {
    List tableau[7];           // 7 Tableau columns
    Stack<Card> foundation[4];       // 4 Foundation piles
    Stack<Card> stockpile;           // Stockpile of cards
    Stack<Card> wastepile;           // Wastepile of drawn cards
    Stack<Command> undoStack;           // Stack of undo commands

public:
    Game();                    // Constructor
    void setupNewGame();        // Set up and shuffle cards
    void printGameState();      // Display the current game state
    void processMove(const string& input); // Process user input commands
    void play();
    void undo();                // Undo last move
    bool isGameOver();  // Check if the game is won or no moves left
    bool isGameWon(); 
    bool noMoreMoves();
    bool canMoveTableauToTableau(int src, int dest);
    bool canMoveToFoundation(Card* card);
    bool canMoveToTableau(Card* card);
};

