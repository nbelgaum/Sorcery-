#include "minion.h"

using namespace std;

Minion::Minion(int cost, std::string n, std::string d, std::string t, int a, int de, int ac) : cost(cost), name(n), descr(d), type(t),attack(a), defence(de), abilityCost(ac) { }

int Minion::getCost() { return cost;}

int Minion::getAbilityCost() { return abilityCost; }

std::string Minion::getName() { return name;}

std::string Minion::getDescr() { return descr;}

std::string Minion::getType() { return type;}

int Minion::getAttack() { return attack; }

int Minion::getDefence() { return defence; }

int Minion::getAction() { return action; }

void Minion::setAttack(int value) { attack = value; }

void Minion::setDefence(int value) { defence = value; }

void Minion::setAbilityCost(int value) {
    abilityCost = value;
}

void Minion::setHaste(bool value) {
    isHaste = value;
}

void Minion::setAbility(bool value) {
    useAbility = value;
}

void Minion::setAction(int value) {
    action = value;
}

std::vector<Card *> & Minion::getEnchants() { return enchantments; }

void Minion::addEnchant(Card * enchant) {
    enchantments.emplace_back(enchant);
}

void Minion::removeEnchant() {                                  // Called when the spell "Disenchant" is played
    Card * enchant = enchantments.at(enchantments.size() - 1);
    string enchantName = enchant->getName();
    if(enchantName == "Giant Strength") {             //
        setAttack(getAttack() - 2);                    //
        setDefence(getDefence() - 2);                   //
    } else if(enchantName == "Enrage") {                 //
        setAttack(getAttack() / 2);                       //
        setDefence(getDefence() / 2);                      //
    } else if(enchantName == "Haste") {                     //
        setHaste(false);                                     //   Reversing the action of the enchantment to be removed
        int max = 0 > action - 1 ? 0 : action - 1;         //
        action = max;                                    //
    } else if(enchantName == "Magic Fatigue") {        //
        setAbilityCost(getAbilityCost() - 2);        //
    } else if(enchantName == "Silence") {          //
        setAbility(true);                        //
    }
    
    enchantments.pop_back();
}


void Minion::takeAction(Player & whoFrom, bool testing,  char index) {
    Info newInfo;
    newInfo.t = Type::Minion;
    newInfo.n = getName();
    newInfo.oldMagic = whoFrom.getMagic();
    if((abilityCost <= whoFrom.getMagic() || testing) && useAbility && action > 0) {  // checking if player has enough magic to use the ability
                                                                                      // or if the testing mode is on and if enough actions are left
        
        if(!testing || (testing && abilityCost <= whoFrom.getMagic())) {
            whoFrom.setMagic(whoFrom.getMagic() - abilityCost);                       // Checking if player's magic has to be deducted
        } else {                                                                      // OR
            whoFrom.setMagic(0);                                                      // to set it to zero
        }
        action -= 1;
        if(index == 0) {
            // Do nothing                        // If index is 0 that means the ability is just used
        } else {                                 // OR
            State state = whoFrom.getState();    // A target is set to use the ability on
            if(state.whose == Whose::Mine) {
                newInfo.target = Target::Me;
            } else {
                newInfo.target = Target::Opp;
            }
            newInfo.index = index;
        }
        whoFrom.setInfo(newInfo);
        whoFrom.update();
    } else {
        cerr << "Not enough magic or action to use the ability" << endl;
        InvalidMove move;                                  // Throwing an object of InvalidMove class
        throw move;                                        // as the player does not have enough magic
    }
}

void  Minion::notify(Player & whoFrom) {
    State state = whoFrom.getState();
    string cardName = getName();
    Info info;
    if(state.time == Trigger::MinExit && cardName == "Bone Golem") {                                              //
        attack++;                                                                                                   //
        defence++;                                                                                                    //
    } else if(state.time == Trigger::MinEnter && cardName == "Fire Elemental" && state.whose == Whose::Opponent) {      //
        info.n = cardName;                                                                                                //
        info.target = Target::Opp;                                                                                          //
        info.t = Type::Minion;                                                                                                //
        whoFrom.setInfo(info);                                                                                                 //  Checking for correct conditions to
        whoFrom.update();                                                                                                    //    activate the trigger of the minion
    } else if(state.time == Trigger::End && cardName == "Potion Seller" && state.whose == Whose::Mine) {                   //      if it has one
        info.n = cardName;                                                                                               //
        info.t = Type::Minion;                                                                                         //
        whoFrom.setInfo(info);                                                                                       //
        whoFrom.update();                                                                                          //
    }                                                                                                            //
}

void Minion::replenishAction() {
    action++;             // Grant the minion an action at the start of the player's turn
    if(isHaste) {
        action++;         // Grant an extra action if the minion is in haste
    }
}

void Minion::endAction() {
    action = 0;              // Make the action zero at the end of player's turn
}

Minion::~Minion() {
  for(auto & ob : enchantments) {    // deleting all the enchantments that the minion has
     delete ob;
  }
}




