#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <vector>
#include <string>
#include <algorithm>

#include "card.h"
#include "state.h"
#include "info.h"
#include "constants.h"
#include "inavlidmove.h"

class Card;        // Forward declaration of class Card

class Player {
    std::string myName;
    int life = 20, magic = 0;
    bool isBonus = false;
    Player * opponent = nullptr;
    std::vector<Card *> hand;       // A vector of Card object pointers to keep track of the cards in player's hand
    std::vector<Card *> minions;    // A vector of Card object pointers to keep track of the minions in play
    std::vector<Card *> ritual;     // A vector of Card object pointers to keep track of the ritual played
    std::vector<Card *> grave;      // A vector of Card object pointers to keep track of the minions who died
    std::vector<Card *> deck;       // A vector of Card object pointers to keep track of the cards to draw
    State state;
    Info info;
    
    public :
    
    // Constructor
    Player(std::string name, std::vector<std::string>, bool bonus);
    
    
    // Getters and setters
    State getState();
    void setState(State newState);
    Info getInfo();
    void setInfo(Info newInfo);
    int getLife();
    int getMagic();
    std::string getMyName();
    void setLife(int l);
    void setMagic(int m);
    void setBonus(bool val);
    std::vector<Card *> & getMinions();
    std::vector<Card *> & getHand();
    std::vector<Card *> & getGrave();
    std::vector<Card *> & getRitual();
    void setOpponent(Player * opp);
    void addToHands(Card *);
    void attachObservers(Card * c);   // Called when a minion or ritual is played
    
    // Called to notify the observers whenever a trigger of any type takes place
    void notifyObservers();
    
    // Called by observers to update according to their specification
    void update();

    // Called at the start of player's turn
    void myStart();
    
    // Called at the end of player's turn
    void myEnd();
    
    // A function to draw a card from the deck and place it in player's hand
    void drawCard();
    
    // Called to discard a card from the player's hand
    void discard(int cardindex);
    
    // A function to check if the player is dead
    bool isPlayerDead();
    
    // A function to remove the dead minions from play and put them in grave
    void removeDeadMinions();
    
    // A function to remove the ritual in play
    void destroyRitual();
    
    // Called to attack the opponent with the desired minion
    void attackPlayer(int minionIndex);
    
    // Called to attack the opponent's desired minion with the desired minion of the active player
    void attackMinion(int myMinIndex, int oppMinIndex);
    
    // Called to either play a minion, ritual or spell with no target
    void play(int cardindex, bool testing);
    
    // Called to play a spell or enchantment with a target
    void play(int myIndex, int player, char vicIndex, bool testing);
    
    // Called to use the ability of a minion with no target
    void use(int minionIndex, bool testing);
    
    // Called to use the ability of a minion with a target
    void use(int minionIndex, int player, char vicIndex, bool testing);

    // Destructor
    ~Player();

};

#endif
