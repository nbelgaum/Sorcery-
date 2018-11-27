#ifndef MINION_H
#define MINION_H

#include <iostream>

#include "card.h"

class Player;       // Forward declaration of class Player

class Minion : public Card {
    
    int attack, defence, abilityCost, cost, action = 1;    // The attack, defence, ability cost
                                                           // and number of actions left of the minion
    
    std::string name, descr, type;                         // Name, description and type of the card
    bool isHaste = false, useAbility = true;               // Track of if ability can be used and if the minion is in haste
    std::vector<Card *> enchantments;                      // A vector of enchantmnets played on the minion
    
    public :
    
    // Constructor
    Minion(int cost, std::string name, std::string desc, std::string type, int a, int d, int ac);
    
    // Getters and setters
    int getAttack();
    int getDefence();
    void setAttack(int value);
    void setDefence(int value);
    int getCost();
    int getAbilityCost();
    void setAbilityCost(int value);
    void setHaste(bool value);
    void setAbility(bool value);
    std::string getName();
    std::string getDescr();
    std::string getType();
    int getAction();
    void setAction(int value);
    std::vector<Card *> & getEnchants();
    void addEnchant(Card *);
    void removeEnchant();
    
    // Called when the player wants to use the ability of the minion
    void takeAction(Player & whoFrom, bool testing, char index = 0);
   
    // Called when trigger of any type takes place
    void notify(Player & whoFrom);
    
    // Called at the start of player's turn
    void replenishAction();
    
    // Called at the end of player's turn
    void endAction();
   
    // Destructor
    ~Minion();
};


#endif

