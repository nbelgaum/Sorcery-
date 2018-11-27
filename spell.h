#ifndef SPELL_H
#define SPELL_H

#include <iostream>

#include "card.h"
#include "state.h"

class Spell : public Card {
    
    int cost;                           // cost of the card
    std::string name, descr, type;      // name, type and descr of the card
    
    public :
    Spell(int cost, std::string name, std::string desc, std::string type);  // Constructor
    
    // Getters
    int getCost();
    std::string getName();
    std::string getDescr();
    std::string getType();
    
    // Called when a spell is played
    void takeAction(Player & whoFrom,  bool testing, char index = 0);
    
    // Notified whenever any kind of trigger is activated
    void notify(Player & whoFrom);
    
    // Called at the start of every player's turn
    void replenishAction();
    
    // Called at the end of every player's turn
    void endAction();

};

#endif

