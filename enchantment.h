#ifndef ENCHANTMENT_H
#define ENCHANTMENT_H

#include <iostream>

#include "card.h"
#include "state.h"

class Enchantment : public Card {
    int cost, strength;            // The cost and the enhancement strength of the
                                   // enchantment card if it has one
    
    std::string name, descr, type, op; // The name, description, type and the strength enhancer
                                       // operator of the enchantment card if it has one
    
    public :
    // Constructor
    Enchantment(int cost, std::string name, std::string desc, std::string type, int strength, std::string op);
    
    // Getters
    int getCost();
    std::string getName();
    std::string getDescr();
    std::string getType();
    
    // Called when an enchantment card is played on a target
    void takeAction(Player & whoFrom,bool testing, char index = 0);
    
    // Called when a trigger of any type takes place
    void notify(Player & whoFrom);
    
    //Called at the start of every turn
    void replenishAction();
    
    // Called at the end of the player's turn
    void endAction();
};


#endif

