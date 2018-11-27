#include "spell.h"

using namespace std;

Spell::Spell(int cost, std::string n, std::string d, std::string t) : cost(cost), name(n), descr(d), type(t) {}

int Spell::getCost() { return cost;}

std::string Spell::getName() { return name;}

std::string Spell::getDescr() { return descr;}

std::string Spell::getType() { return type;}

void Spell::takeAction(Player & whoFrom,  bool testing, char index) {
    int magic = whoFrom.getMagic();         // getting the magic of the player
    State state = whoFrom.getState();
    int cost = getCost();
    if(cost <= magic || testing) {          // checking if player has enough magic to play the spell
                                            // or if the testing mode is on
        Info newInfo;
        if(state.whose == Whose::Opponent) {     //
            newInfo.target = Target::Opp;         //
        } else {                                    // Setting the target player of the spell
            newInfo.target = Target::Me ;         //
        }                                       //
        newInfo.t = Type::Spell;
        newInfo.n = getName();
        newInfo.index = index;
        newInfo.oldMagic = magic;
        whoFrom.setInfo(newInfo);
        if(!testing || (testing && (cost <= magic))) {
            whoFrom.setMagic(magic - cost);              // Checking if player's magic has to be deducted
        } else {                                         // OR
            whoFrom.setMagic(0);                         // set to zero has player does not have enough magic
        }
        whoFrom.update();
    } else {
        cerr << "Not enough magic to play the card" << endl;
        InvalidMove move;                                           // Throwing an object of InvalidMove
        throw move;                                                 // as the testing mode was off and player did not have magic
    }
}


void Spell::notify(Player & whoFrom) {
    // do nothing
}


void Spell::replenishAction() {
    // Do nothing
}

void Spell::endAction() {
    // do nothing
}


