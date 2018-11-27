#ifndef CARD_H
#define CARD_H

#include <string>

#include "player.h"
#include "info.h"
#include "state.h"

class Player;    // Forward declaration of class Player

class Card {     // An abstract class
   
    public :
    
    // Getters
    virtual std::string getDescr() = 0;
    virtual std::string getName() = 0;
    virtual std::string getType() = 0;
    virtual int getCost() = 0;
    
    // Called when any card is played
    virtual void takeAction(Player & whoFrom, bool testing, char index = 0) = 0;
    
    // Called when a trigger of any type takes place
    virtual void notify(Player & whoFrom) = 0;
   
    // Called at the start of player's turn
    virtual void replenishAction() = 0;
    
    // Called at the end of player's turn
    virtual void endAction() = 0;
    
    // Destructor
    virtual ~Card() = default;
};

#endif

