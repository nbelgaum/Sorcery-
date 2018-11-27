#include "enchantment.h"

using namespace std;

Enchantment::Enchantment(int cost, std::string n, std::string d, std::string t, int s, std::string o) : cost(cost), name(n), type(t), strength(s), op(o) {}

int Enchantment::getCost() { return cost;}

std::string Enchantment::getName() { return name;}

std::string Enchantment::getDescr() { return descr;}

std::string Enchantment::getType() { return type;}

void Enchantment::takeAction(Player & whoFrom,bool testing,  char index) {
    int magic = whoFrom.getMagic();       // getting the magic of the player
    State state = whoFrom.getState();
    int cost = getCost();
    if(cost <= magic) {                    // checking if player has enough magic to play the enchantment
    Info newInfo;
        if(state.whose == Whose::Opponent) {       //
            newInfo.target = Target::Opp;           //
        } else {                                     //  Setting the target player of the enchantment
            newInfo.target = Target::Me;           //
        }                                        //
        newInfo.t = Type::Enchantment;
        newInfo.n = getName();
        newInfo.index = index;
        newInfo.oldMagic = magic;
        whoFrom.setInfo(newInfo);
        whoFrom.setMagic(magic - cost);
        whoFrom.update();
    } else {
        cerr << "Not enough magic to play the card" << endl;
        InvalidMove move;         			        // Throwing an object of InvalidMove
        throw move;                     		        // as player did not have magic to play the enchant
    }
}


void Enchantment::notify(Player & whoFrom) {
    // do nothing
}

void Enchantment::replenishAction() {
    // Do nothing
}

void Enchantment::endAction() {
    // Do nothing
}


