#include "ritual.h"

using namespace std;

Ritual::Ritual(int cost, std::string n, std::string d, std::string t, int c, int ac) :  cost(cost), name(n), descr(d), type(t), charge(c), abilityCost(ac) { }

int Ritual::getCharge() {
    return charge;
}

void Ritual::setCharge(int value) {
    charge = value;
}

int Ritual::getCost() { return cost;}

int Ritual::getAbilityCost() { return abilityCost; }

std::string Ritual::getName() { return name;}

std::string Ritual::getDescr() { return descr;}

std::string Ritual::getType() { return type;}

void Ritual::takeAction(Player & whoFrom, bool testing, char index) {
    // Do nothing
}

void Ritual::notify(Player & whoFrom) {
    State state = whoFrom.getState();
    string cardName = getName();
    if((state.time == Trigger::Start && cardName == "Dark Ritual" && state.whose == Whose::Mine) ||        // Checking for correct
       (state.time == Trigger::MinEnter && cardName == "Aura of Power" && state.whose == Whose::Mine) ||   // conditions to activate the ritual
       (state.time == Trigger::MinEnter && cardName == "Standstill") ||                                   // based on type of trigger
       (state.time == Trigger::MinEnter && cardName == "White Defence" && state.whose == Whose::Opponent)) {
        if(charge >= abilityCost) {       // Checking if enough charges are left
            Info newInfo;
            newInfo.t = Type::Ritual;
            newInfo.n = cardName;
            if(state.whose == Whose::Mine) {               // Setting the target as Standstill destroys any minion that enters play
                newInfo.target = Target::Me;
            } else {
                newInfo.target = Target::Opp;
            }
            charge -= abilityCost;            // Deducting the charges
            whoFrom.setInfo(newInfo);
            whoFrom.update();
        }
    }
}

void Ritual::replenishAction() {
    // Do nothing
}

void Ritual::endAction() {
    // Do nothing
}
