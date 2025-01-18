#pragma once
#include<iostream>
#include"Command.h"


//Getters
    char Command::getType()  { return type; }
    int Command::getSource()  { return src; }
    int Command::getDestination()  { return dest; }
    int Command::getNumCards()  { return numCards; }

//Setters (if needed for undo)
    void Command::setSource(int s) { src = s; }
    void Command::setDestination(int d) { dest = d; }
    void Command::setNumCards(int n) { numCards = n; }