#pragma once
class Command
{
private:
	int src, dest, numCards;
	char type;
public:
    Command(const char t, int s, int d, int n = 1) : type(t), src(s), dest(d), numCards(n) {}

    // Getters
    char getType();
    int getSource();
    int getDestination();
    int getNumCards();

    // Setters (if needed for undo)
    void setSource(int s);
    void setDestination(int d);
    void setNumCards(int n);
};