#ifndef RITUAL_H
#define RITUAL_H

#include "card.h"

class Ritual : public Card {
    
    int charge, abilityCost, cost;  // Charges, ability cost and the cost of the card
    std::string name, descr, type;  // Name, description and type of the card
    
    public :
    
    // Constructor
    Ritual(int cost, std::string name, std::string desc, std::string type, int c, int ac);
    
    // Getters and setters
    int getCharge();
    void setCharge(int value);
    int getCost();
    int getAbilityCost();
    std::string getName();
    std::string getDescr();
    std::string getType();
    
    // Called when a ritual card is played
    void takeAction(Player & whoFrom, bool testing,  char index = 0);
    
    // Called when a trigger of any type takes place
    void notify(Player & whoFrom);
    
    // Called at the start of player's turn
    void replenishAction();
    
    // Called at the end of player's turn
    void endAction();
};

#endif

