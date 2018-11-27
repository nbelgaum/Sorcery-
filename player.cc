#include <iostream>
#include <stdio.h>

#include "player.h"
#include "ritual.h"
#include "minion.h"
#include "spell.h"
#include "enchantment.h"


using namespace std;

Player::Player(std::string name, std::vector<std::string> deckOfCards, bool bonus) : myName(name), isBonus(bonus) {
    for(auto & ob : deckOfCards) {
        Card * newCard = nullptr;
        if(ob == "Mag" && isBonus) {
            newCard = new Spell(3, mag, suckerDescr, "Spell");
        } else if(ob == "Banish") {
            newCard = new Spell(2, ba, banishDecsr, "Spell");
        } else if(ob == "Unsummon") {
            newCard = new Spell(1, un, unsummonDecsr, "Spell");
        } else if(ob == "Recharge") {
            newCard = new Spell(1, re, rechargeDecsr, "Spell");
        } else if(ob == "Disenchant") {
            newCard = new Spell(1, dis, disenDecsr, "Spell");
        } else if(ob == "Raise") {
            newCard = new Spell(1, rd, raiseDecsr, "Spell");
        } else if(ob == "Blizzard") {
            newCard = new Spell(3, bl, blizzardDecsr, "Spell");
        } else if(ob == "Air") {
            newCard = new Minion(0, ae, emp, "Minion", 1, 1, 0);
        } else if(ob == "Earth") {
            newCard = new Minion(3, ee, emp, "Minion", 4, 4, 0);
        } else if(ob == "Bone") {
            newCard = new Minion(2, bg, boneDecsr, "Minion", 1, 3, 0);
        } else if(ob == "Fire") {
            newCard = new Minion(2, fe, fireDecsr, "Minion", 2, 2, 0);
        } else if(ob == "Potion") {
            newCard = new Minion(2, ps, potionDecsr, "Minion", 1, 3, 0);
        } else if(ob == "Novice") {
            newCard = new Minion(1, np, noviceDecsr, "Minion", 0, 1, 1);
        } else if(ob == "Apprentice") {
            newCard = new Minion(1, as, apprenticeDecsr, "Minion", 1, 1, 1);
        } else if(ob == "Master") {
            newCard = new Minion(3, ms, masterDecsr, "Minion", 2, 3, 2);
        } else if(ob == "Giant") {
            newCard = new Enchantment(1, gs, emp, "Enchantment", 2, "+");
        } else if(ob == "Enrage") {
            newCard = new Enchantment(2, en, emp, "Enchantment", 2, "*");
        } else if(ob == "Haste") {
            newCard = new Enchantment(1, ha, hasteDecsr, "Enchantment", 0, "");
        } else if(ob == "Magic") {
            newCard = new Enchantment(0, mf, magicDecsr, "Enchantment", 0, "");
        } else if(ob == "Silence") {
            newCard = new Enchantment(1, si, silenceDecsr, "Enchantment", 0, "");
        } else if(ob == "Dark") {
            newCard = new Ritual(0, dr, darkDecsr, "Ritual", 5, 1);
        } else if(ob == "Aura") {
            newCard = new Ritual(1, aof, auracDecsr, "Ritual", 4, 1);
        } else if(ob == "Standstill") {
            newCard = new Ritual(3, ss, standDecsr, "Ritual", 4, 2);
        } else if(ob == "White" && isBonus) {
            newCard = new Ritual(3, wd, whiteDecsr, "Ritual", 4, 2);
        }
        if(newCard != nullptr) {
            deck.emplace_back(newCard);
        }
    }
}

State Player::getState() {
    return state;
}

void Player::setState(State newState) {
    state = newState;
}

Info Player::getInfo() {
    return info;
}

void Player::setInfo(Info newInfo) {
    info = newInfo;
}

int Player::getLife() { return life; }

int Player::getMagic() { return magic; }

std::string Player::getMyName() { return myName; }

void Player::setLife(int l) { life = l;}

void Player::setMagic(int m) { magic = m; }

void Player::setBonus(bool val) {
    isBonus = val;
}

std::vector<Card *> & Player::getMinions() {
    return minions;
}

std::vector<Card *> & Player::getHand() {
    return hand;
}

std::vector<Card *> & Player::getGrave() {
    return grave;
}

std::vector<Card *> & Player::getRitual() {
    return ritual;
}

void Player::addToHands(Card * c) {
    hand.emplace_back(c);
}

void Player::setOpponent(Player * opp) {
    opponent = opp;
}

void Player::attachObservers(Card * c) {
    std::string type = c->getType();
    int cost = c->getCost();
    if(type == "Minion" && minions.size() < 5 && cost <= magic) {       // Checking if already 5 minions are in play
        magic -= cost;
        minions.emplace_back(c);
        State newState, oppState;
        newState.time = Trigger::MinEnter;
        oppState.time = Trigger::MinEnter;
        oppState.whose = Whose::Opponent;
        newState.whose = Whose::Mine;
        setState(newState);
        opponent->setState(oppState);
        notifyObservers();
        opponent->notifyObservers();
    } else if(type == "Ritual" && cost <= magic) {
        ritual.clear();             // Removing the old ritual in order to place a new one
        ritual.emplace_back(c);
        magic -= cost;
    } else {
        cerr << "Either 5 minions are already in play or you do not have enough magic to play the card" << endl;
        InvalidMove move;
        throw move;
    }
}


void Player::notifyObservers() {
    for(auto & ob : minions) {      // Notifying minions so that they get notified of the trigger
        ob->notify(*this);
    }
    
    for(auto & ob : ritual) {
        ob->notify(*this);         // Notifying ritual so that it gets notified of the trigger
    }
}

void Player::update() {
    State newState, oppState;
    Info info = getInfo();
    Type type = info.t;
    int om = info.oldMagic;
    string name = info.n;
    Target who = info.target;
    int vicIndex;
    char vic  = info.index;
    if(vic == '1') {                //
        vicIndex = 1;                //
    } else if(vic == '2') {           //
        vicIndex = 2;                  //
    } else if(vic == '3') {             // Setting the index of the target minion
        vicIndex = 3;                 //
    } else if(vic == '4') {         //
        vicIndex = 4;             //
    } else if(vic == '5') {     //
        vicIndex = 5;
    }
    
    if(type == Type::Enchantment) {           // Checking the type of the card which called the function
        Minion * minion;
        vector <Card *> enemeyMinions = opponent->getMinions();
        
        if(who == Target::Me) {
            try {
                minion = dynamic_cast<Minion *>(minions.at(vicIndex - 1));
            } catch (out_of_range) {
                cerr << "Target minion not found" << endl;
                InvalidMove move;
                move.correction = om;
                throw move;
            }
        } else {
            try {
                minion = dynamic_cast<Minion *>(enemeyMinions.at(vicIndex - 1));
            } catch (out_of_range) {
                cerr << "Target minion not found" << endl;
                InvalidMove move;
                move.correction = om;
                throw move;
            }
        }
        if(name == "Giant Strength") {
            minion->setAttack(minion->getAttack() + 2);
            minion->setDefence(minion->getDefence() + 2);
            minion->addEnchant(new Enchantment(1, gs, emp, "Enchantment", 2, "+"));
        } else if(name == "Enrage") {
            minion->setAttack(minion->getAttack() * 2);
            minion->setDefence(minion->getDefence() * 2);
            minion->addEnchant(new Enchantment(2, en, emp, "Enchantment", 2, "*"));
        } else if(name == "Haste") {
            minion->setHaste(true);
            int min = 2 < minion->getAction() + 1 ? 2 : minion->getAction() + 1;
            minion->setAction(min);
            minion->addEnchant(new Enchantment(1, ha, hasteDecsr, "Enchantment", 0, ""));
        } else if(name == "Magic Fatigue") {
            minion->setAbilityCost(minion->getAbilityCost() + 2);
            minion->addEnchant(new Enchantment(0, mf, magicDecsr, "Enchantment", 0, ""));
        } else if(name == "Silence") {
            minion->setAbility(false);
            minion->addEnchant(new Enchantment(1, si, silenceDecsr, "Enchantment", 0, ""));
        }
        
        if(who == Target::Opp) {
            opponent->getMinions() = enemeyMinions;
        }
        
    } else if(type == Type::Spell) {
        if(name == "Mag Sucker") {
            if(opponent->getMagic() > 0 && isBonus) {
                setMagic(opponent->getMagic() + getMagic() + 3);
                opponent->setMagic(0);
            } else {
                cerr << "Not enough magic to suck out of opponent or bonus is disabled" << endl;
                InvalidMove move;
                move.correction = om;
                throw move;
            }
        } else if(name == "Banish") {
            if(vic == 'r' && who == Target::Me) {
                if(ritual.size() == 0) {
                    InvalidMove move;
                    move.correction = om;
                    throw move;
                }
                destroyRitual();
            } else if(vic == 'r' && who == Target::Opp) {
                if((opponent->getRitual()).size() == 0) {
                    InvalidMove move;
                    move.correction = om;
                    throw move;
                }
                opponent->destroyRitual();
            } else if(who == Target::Me) {
                int index = vicIndex - 1;
                int size = minions.size();
                if(index < size && index >= 0) {
                    minions.erase(minions.begin() + index);
                } else {
                    cerr << "Target minion not found" << endl;
                    InvalidMove move;
                    move.correction = om;
                    throw move;
                }
                newState.time = Trigger::MinExit;
                oppState.time = Trigger::MinExit;
                newState.whose = Whose::Mine;
                oppState.whose = Whose::Opponent;
                setState(newState);
                opponent->setState(oppState);
                notifyObservers();
                opponent->notifyObservers();
            } else {
                int index = vicIndex - 1;
                vector <Card *> enemeyMinions = opponent->getMinions();
                int enSize = enemeyMinions.size();
                if(index < enSize && index >= 0) {
                    enemeyMinions.erase(enemeyMinions.begin() + index);
                } else {
                    cerr << "Target minion not found" << endl;
                    InvalidMove move;
                    move.correction = om;
                    throw move;
                }
                opponent->getMinions() = enemeyMinions;
                newState.time = Trigger::MinExit;
                oppState.time = Trigger::MinExit;
                newState.whose = Whose::Opponent;
                oppState.whose = Whose::Mine;
                setState(newState);
                opponent->setState(oppState);
                notifyObservers();
                opponent->notifyObservers();
            }
        } else if(name == "Unsummon") {
            newState.time = Trigger::MinExit;
            oppState.time = Trigger::MinExit;
            int index = vicIndex - 1;
            if(who == Target::Me) {
                newState.whose = Whose::Mine;
                oppState.whose = Whose::Opponent;
                int size = minions.size();
                if(index < size && index >= 0) {
                    Card * uCard = minions.at(index);
                    minions.erase(minions.begin() + index);
                    addToHands(uCard);
                } else {
                    cerr << "Target minion not found" << endl;
                    InvalidMove move;
                    move.correction = om;
                    throw move;
                }
            } else {
                newState.whose = Whose::Opponent;
                oppState.whose = Whose::Mine;
                vector <Card *> enemeyMinions = opponent->getMinions();
                int enSize = enemeyMinions.size();
                if(index < enSize && index >= 0) {
                    Card * uCard = enemeyMinions.at(index);
                    enemeyMinions.erase(enemeyMinions.begin() + index);
                    opponent->getMinions() = enemeyMinions;
                    opponent->addToHands(uCard);
                } else {
                    cerr << "Target minion not found" << endl;
                    InvalidMove move;
                    move.correction = om;
                    throw move;
                    
                }
            }
            setState(newState);
            opponent->setState(oppState);
            notifyObservers();
            opponent->notifyObservers();
        } else if(name == "Recharge") {
            if(ritual.size() == 1) {
                Ritual * ritual = dynamic_cast<Ritual *>(Player::ritual[0]);
                if(ritual != 0) {
                    int oldcharges = ritual->getCharge();
                    oldcharges += 3;
                    ritual->setCharge(oldcharges);
                }
                
            } else {
                cerr << "No ritual card present in play" << endl;
                InvalidMove move;
                move.correction = om;
                throw move;
            }
            
        } else if(name == "Disenchant") {
            Minion * minion;
            if(who == Target::Me) {
                try {
                    minion = dynamic_cast<Minion *>(minions.at(vicIndex - 1));
                } catch (out_of_range) {
                    cerr << "Minion not found" << endl;
                    InvalidMove move;
                    move.correction = om;
                    throw move;
                }
                if((minion->getEnchants()).size() == 0) {
                    InvalidMove move;
                    move.correction = om;
                    throw move;
                }
                if(minion != 0) {
                    minion->removeEnchant();
                }
                removeDeadMinions();
            } else {
                try {
                    minion = dynamic_cast<Minion *>((opponent->getMinions()).at(vicIndex - 1));
                } catch (out_of_range) {
                    cerr << "Minion not found" << endl;
                    InvalidMove move;
                    move.correction = om;
                    throw move;
                }
                if((minion->getEnchants()).size() == 0) {
                    InvalidMove move;
                    move.correction = om;
                    throw move;
                }
                if(minion != 0) {
                    minion->removeEnchant();
                }
                opponent->removeDeadMinions();
            }
            
        } else if(name == "Raise Dead") {
            if(grave.size() != 0 && minions.size() < 5) {
                Card * deadCard = grave.at(grave.size() - 1);
                Minion * minion = dynamic_cast<Minion *>(deadCard);
                minion->setDefence(1);
                minions.emplace_back(deadCard);
                grave.pop_back();
                newState.time = Trigger::MinEnter;
                oppState.time = Trigger::MinEnter;
                newState.whose = Whose::Mine;
                oppState.whose = Whose::Opponent;
                setState(newState);
                opponent->setState(oppState);
                notifyObservers();
                opponent->notifyObservers();
            } else {
                cerr << "Either there is no minion in grave or 5 minions already in play" << endl;
                InvalidMove move;
                move.correction = om;
                throw move;
            }
            
        } else if(name == "Blizzard") {
            for(auto & ob : minions) {
                Minion * minion = dynamic_cast<Minion *>(ob);
                if(minion != 0) {
                    minion->setDefence(minion->getDefence() - 2);
                }
            }
            
            removeDeadMinions();
            
            vector<Card *> enemyMinions = opponent->getMinions();
            for(auto & ob : enemyMinions) {
                Minion * minion = dynamic_cast<Minion *>(ob);
                if(minion != 0) {
                    minion->setDefence(minion->getDefence() - 2);
                }
            }
            opponent->getMinions() = enemyMinions;
            opponent->removeDeadMinions();
        }
        
    } else if(type == Type::Minion) {
        if(name == "Fire Elemental") {
            vector <Card *> enemeyMinions = opponent->getMinions();
            Minion * enemey = dynamic_cast<Minion *>(enemeyMinions.at(enemeyMinions.size() - 1));
            enemey->setDefence(enemey->getDefence() - 1);
            opponent->getMinions() = enemeyMinions;
            opponent->removeDeadMinions();
        } else if(name == "Potion Seller") {
            for(auto & ob : minions) {
                Minion * minion = dynamic_cast<Minion *>(ob);
                if(minion != 0) {
                    minion->setDefence(minion->getDefence() + 1);
                }
            }
        } else if(name == "Novice Pyromancer") {
            if(who == Target::Opp) {
                vector <Card *> enemyMinions = opponent->getMinions();
                try {
                    Minion * min = dynamic_cast<Minion *>(enemyMinions.at(vicIndex - 1));
                    min->setDefence(min->getDefence() - 1);
                    opponent->getMinions() = enemyMinions;
                    opponent->removeDeadMinions();
                    
                } catch (out_of_range) {
                    cerr << "Target minion not found" << endl;
                    InvalidMove move;
                    move.correction = om;
                    throw move;
                }
            } else {
                try {
                    Minion * min = dynamic_cast<Minion *>(minions.at(vicIndex - 1));
                    min->setDefence(min->getDefence() - 1);
                    removeDeadMinions();
                } catch (out_of_range) {
                    cerr << "Target minion not found" << endl;
                    InvalidMove move;
                    move.correction = om;
                    throw move;
                }
            }
            
        } else if(name == "Apprentice Summoner") {
            if(minions.size() < 5) {
                Card * newCard = new Minion(0, ae,emp, "Minion", 1, 1, 0);
                minions.emplace_back(newCard);
                newState.time = Trigger::MinEnter;
                oppState.time = Trigger::MinEnter;
                newState.whose = Whose::Mine;
                oppState.whose = Whose::Opponent;
                setState(newState);
                opponent->setState(oppState);
                notifyObservers();
                opponent->notifyObservers();
            } else {
                cerr << "Not enough space to add a minion" << endl;
                InvalidMove move;
                move.correction = om;
                throw move;
            }
            
        } else if(name == "Master Summoner") {
            if(minions.size() < 5) {
                int loopSize = 3 < 5 - minions.size() ? 3 : 5 - minions.size();
                if(loopSize > 0) {
                    for(int i = 0; i < loopSize; i++) {
                        Card * newCard = new Minion(0, ae, emp, "Minion", 1, 1, 0);
                        minions.emplace_back(newCard);
                        newState.time = Trigger::MinEnter;
                        oppState.time = Trigger::MinEnter;
                        newState.whose = Whose::Mine;
                        oppState.whose = Whose::Opponent;
                        setState(newState);
                        opponent->setState(oppState);
                        notifyObservers();
                        opponent->notifyObservers();
                    }
                }
            } else {
                cerr << "Not enough space to add a minion" << endl;
                InvalidMove move;
                move.correction = om;
                throw move;
            }
        }
    } else {
        if(name == "Dark Ritual") {
            magic++;
        } else if(name == "Aura of Power") {
            Minion * minion = dynamic_cast<Minion *>(minions.at(minions.size() - 1));
            if(minion != 0) {
                int oldAttack = minion->getAttack(), oldDefence = minion->getDefence();
                oldAttack++; oldDefence++;
                minion->setAttack(oldAttack);
                minion->setDefence(oldDefence);
            }
            
        } else if(name == "Standstill") {
            newState.time = Trigger::MinExit;
            oppState.time = Trigger::MinExit;
            if(info.target == Target::Me) {
                minions.pop_back();
                newState.whose = Whose::Mine;
                oppState.whose = Whose::Opponent;
            } else {
                vector <Card *> enemyMinions = opponent->getMinions();
                enemyMinions.pop_back();
                opponent->getMinions() = enemyMinions;
                newState.whose = Whose::Opponent;
                oppState.whose = Whose::Mine;
            }
            setState(newState);
            opponent->setState(oppState);
            notifyObservers();
            opponent->notifyObservers();
        } else if(name == "White Defence") {
            vector <Card *> enemyMinions = opponent->getMinions();
            Minion * min = dynamic_cast<Minion *>(enemyMinions.at(enemyMinions.size() - 1));
            life += min->getDefence();
        }
    }
}

void Player::myStart() {
    magic++;
    drawCard();
    for(auto & ob : minions) {
        ob->replenishAction();
    }
    State newState, oppState;
    newState.time = Trigger::Start;
    oppState.time = Trigger::Start;
    newState.whose = Whose::Mine;
    oppState.whose = Whose::Opponent;
    setState(newState);
    opponent->setState(oppState);
    notifyObservers();
    opponent->notifyObservers();
}

void Player::myEnd() {
    State newState, oppState;
    newState.time = Trigger::End;
    oppState.time = Trigger::End;
    newState.whose = Whose::Mine;
    oppState.whose = Whose::Opponent;
    setState(newState);
    opponent->setState(oppState);
    notifyObservers();
    opponent->notifyObservers();
    for(auto & ob : minions) {
        ob->endAction();
    }
}

void Player::drawCard() {
    if(deck.size() > 0 && hand.size() < 5) {   // Checking if there are already 5 cards in player's hand
        // and if deck is not empty
        Card * newCard = deck[0];
        deck.erase(deck.begin());
        hand.emplace_back(newCard);
    } else {
        cerr << "No card present in deck or hand is already full" << endl;
    }
}

void Player::discard(int cardindex) {
    int handSize = hand.size();
    if(cardindex <= handSize) {
        hand.erase(hand.begin() + (cardindex - 1));
    } else {
        cerr << "card is out of range" << endl;
    }
}

bool Player::isPlayerDead() {
    return life <=  0;
}

void Player::removeDeadMinions() {
    for(unsigned i = 0; i < minions.size(); i++) {
        Minion * minion = dynamic_cast<Minion *>(minions[i]);
        if(minion != 0) {
            if(minion->getDefence() <= 0) {
                Card * deadMinion = minions[i];
                minions.erase(minions.begin() + i);
                grave.emplace_back(deadMinion);
                State newState, oppState;
                newState.time = Trigger::MinExit;
                oppState.time = Trigger::MinExit;
                newState.whose = Whose::Mine;
                oppState.whose = Whose::Opponent;
                setState(newState);
                opponent->setState(oppState);
                notifyObservers();
                deadMinion->notify(*this);
                opponent->notifyObservers();
                i--;      // Subtracting becuase the vector's size will get reduced and a new card will come at the same index
            }
        }
    }
}

void Player::destroyRitual() {
    ritual.clear();
}

void Player::attackPlayer(int minionIndex) {
    try {
        Minion * minion = dynamic_cast<Minion *>(minions.at(minionIndex - 1));
        if(minion != 0) {
            int attackValue = minion->getAttack();
            int oldLife = opponent->getLife();
            if(minion->getAction() > 0) {
                opponent->setLife(oldLife - attackValue);
                minion->setAction(minion->getAction() - 1);
            } else {
                cerr << "Not enough action for this turn" << endl;
            }
        }
    } catch (out_of_range) {
        cerr << "Minion out of range" << endl;
    }
}

void Player::attackMinion(int myMinIndex, int oppMinIndex) {
    try {
        vector<Card *> enemyMinions = opponent->getMinions();
        Minion * enemy = dynamic_cast<Minion *>(enemyMinions.at(oppMinIndex - 1));
        Minion * me = dynamic_cast<Minion *>(minions.at(myMinIndex - 1));
        if (enemy != 0 && me != 0) {
            if(me->getAction() > 0) {
                int enemyAttack = enemy->getAttack();
                int myAttack = me->getAttack();
                enemy->setDefence(enemy->getDefence() - myAttack);
                me->setDefence(me->getDefence() - enemyAttack);
                opponent->getMinions() = enemyMinions;
                removeDeadMinions();
                opponent->removeDeadMinions();
                me->setAction(me->getAction() - 1);
            } else {
                cerr << "Not enough action for this turn" << endl;
            }
        }
    } catch (out_of_range) {
        cerr << "Minion out of range" << endl;
    }
}

void Player::play(int cardindex, bool testing) {
    try {
        Card * newCard = hand.at(cardindex - 1);
        string type = newCard->getType();
        if(type == "Spell") {
            newCard->takeAction(*this, testing);
            hand.erase(hand.begin() + (cardindex - 1));
            
        } else {
            attachObservers(newCard);
            hand.erase(hand.begin() + (cardindex - 1));
        }
    } catch (InvalidMove & move) {
        magic = move.correction;
    } catch(out_of_range) {
        cerr << "Card was not found in hand of the player" << endl;
    }
}

void Player::play(int myIndex, int player, char vicIndex, bool testing) {
    State newState;
    if(player == 1) {
        newState.whose = Whose::Mine;
    } else {
        newState.whose = Whose::Opponent;
    }
    setState(newState);
    try {
        Card * newCard = hand.at(myIndex - 1);
        newCard->takeAction(*this, testing, vicIndex);
        hand.erase(hand.begin() + (myIndex - 1));
    } catch (InvalidMove & move) {
        magic = move.correction;
    } catch(out_of_range) {
        cerr << "Card was not found in hand of the player" << endl;
    }
}

void Player::use(int minionIndex, bool testing) {
    try {
        Card * minion = minions.at(minionIndex - 1);
        minion->takeAction(*this, testing);
    } catch (InvalidMove & move) {
        magic = move.correction;
    } catch(out_of_range) {
        cerr << "Minion was not found" << endl;
    }
}

void Player::use(int minionIndex, int player, char vicIndex, bool testing) {
    State newState;
    if(player == 1) {
        newState.whose = Whose::Mine;
    } else {
        newState.whose = Whose::Opponent;
    }
    setState(newState);
    try {
        Card * minion = minions.at(minionIndex - 1);
        minion->takeAction(*this, testing, vicIndex);
    } catch (InvalidMove & move) {
        magic = move.correction;
    } catch(out_of_range) {
        cerr << "Minion was not found" << endl;
    }
}


Player::~Player() {
    for(auto & ob : deck) {
        delete ob;
    }
    
    for(auto & ob : minions) {
        delete ob;
    }
    
    destroyRitual();
    
    for(auto & ob : hand) {
        delete ob;
    }
    
    for(auto & ob : grave) {
        delete ob;
    }
}

