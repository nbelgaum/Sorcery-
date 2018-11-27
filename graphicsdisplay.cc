#include "graphicsdisplay.h"

GraphicsDisplay:: GraphicsDisplay() {
    w = new Xwindow();
}

GraphicsDisplay::~GraphicsDisplay() {
    delete w;
}

using namespace std;
void displaySpell(int x, int y, std::string name, Xwindow * w, int cost) {
    w->fillRectangle(x, y, 100, 100, 0);
    std::string n = "Spell :";
    n += name;
    std::string costString = to_string(cost);
    w->drawString(x + 15, y + 50, n);
    w->fillRectangle(x, y, 100, 5);
    w->fillRectangle(x, y, 5, 100);
    w->fillRectangle(x, y + 95, 100, 5);
    w->fillRectangle(x + 95, y, 5, 100);
    w->drawString(x + 85, y + 15, costString);
}

void displayMinion(int x, int y, std::string name, Xwindow * w, int cost, int attack, int life) {
    w->fillRectangle(x, y, 100, 100, 0);
    std::string n = "Minion :";
    std::string costString = to_string(cost);
    n += name;
    w->drawString(x + 20, y + 50, n);
    w->fillRectangle(x, y, 100, 5);
    w->fillRectangle(x, y, 5, 100);
    w->fillRectangle(x, y + 95, 100, 5);
    w->fillRectangle(x + 95, y, 5, 100);
    w->drawString(x + 85, y + 15, costString);
    w->drawString(x + 15, y + 85, to_string(attack));
    w->drawString(x + 85, y + 85, to_string(life));
}

void displayRitual(int x, int y, std::string name, Xwindow * w, int cost, int abCost, int charges) {
    w->fillRectangle(x, y, 100, 100, 0);
    std::string n = "Ritual :";
    std::string costString = to_string(cost);
    n += name;
    w->drawString(x + 15, y + 50, n);
    w->fillRectangle(x, y, 100, 5);
    w->fillRectangle(x, y, 5, 100);
    w->fillRectangle(x, y + 95, 100, 5);
    w->fillRectangle(x + 95, y, 5, 100);
    w->drawString(x + 85, y + 15, costString);
    w->drawString(x + 85, y + 85, to_string(charges));
    w->drawString(x + 15, y + 85, to_string(abCost));
}

void displayEnchant(int x, int y, std::string name, Xwindow * w, int cost) {
    w->fillRectangle(x, y, 100, 100, 0);
    std::string n = "Enchant :";
    std::string costString = to_string(cost);
    n += name;
    w->drawString(x + 15, y + 50, n);
    w->fillRectangle(x, y, 100, 5);
    w->fillRectangle(x, y, 5, 100);
    w->fillRectangle(x, y + 95, 100, 5);
    w->fillRectangle(x + 95, y, 5, 100);
    w->drawString(x + 85, y + 15, costString);
    
    
}

void displayEmpty(int x, int y, Xwindow * w) {
    w->fillRectangle(x, y, 100, 100);
    w->fillRectangle(x, y, 100, 5);
    w->fillRectangle(x, y, 5, 100);
    w->fillRectangle(x, y + 95, 100, 5);
    w->fillRectangle(x + 95, y, 5, 100);
    
}

void displayName(int x, int y, std::string name, Xwindow * w, int life, int magic, int player) {
    w->fillRectangle(x, y, 100, 100, 0);
    w->drawString(x + 30, y + 50, name);
    w->fillRectangle(x, y, 100, 5);
    w->fillRectangle(x, y, 5, 100);
    w->fillRectangle(x, y + 95, 100, 5);
    w->fillRectangle(x + 95, y, 5, 100);
    if(player == 1) {
        w->drawString(x + 10, y + 85, to_string(life));
        w->drawString(x + 85, y + 85, to_string(magic));
    } else {
        w->drawString(x + 10, y + 15, to_string(life));
        w->drawString(x + 85, y + 15, to_string(magic));
    }
    
}


void displayTheCard(Card * ob, int x, int y, Xwindow * w) {
    string cardName = ob->getName();
    int cost = ob->getCost();
    Minion * min = dynamic_cast<Minion *>(ob);
    Ritual * rit = dynamic_cast<Ritual *>(ob);
    
    if(cardName == "Mag Sucker") {
        displaySpell(x, y, "MAG", w, cost);
    } else if(cardName == "Banish") {
        displaySpell(x, y, "BA", w, cost);
    } else if(cardName == "Unsummon") {
        displaySpell(x, y, "UN", w, cost);
    } else if(cardName == "Recharge") {
        displaySpell(x, y, "RE", w, cost);
    } else if(cardName == "Disenchant") {
        displaySpell(x, y, "DIS", w, cost);
    } else if(cardName == "Raise Dead") {
        displaySpell(x, y, "RD", w, cost);
    } else if(cardName == "Blizzard") {
        displaySpell(x, y, "BL", w, cost);
    } else if(cardName == "Air Elemental") {
        displayMinion(x, y, "AE", w, cost, min->getAction(), min->getDefence());
    } else if(cardName == "Earth Elemental") {
        displayMinion(x, y, "EE", w, cost, min->getAction(), min->getDefence());
    } else if(cardName == "Bone Golem") {
        displayMinion(x, y, "BG", w, cost, min->getAction(), min->getDefence());
    } else if(cardName == "Fire Elemental") {
        displayMinion(x, y, "FE", w, cost, min->getAction(), min->getDefence());
    } else if(cardName == "Potion Seller") {
        displayMinion(x, y, "PS", w, cost, min->getAction(), min->getDefence());
    } else if(cardName == "Novice Pyromancer") {
        displayMinion(x, y, "NP", w, cost, min->getAction(), min->getDefence());
    } else if(cardName == "Apprentice Summoner") {
        displayMinion(x, y, "AS", w, cost, min->getAction(), min->getDefence());
    } else if(cardName == "Master Summoner") {
        displayMinion(x, y, "MS", w, cost, min->getAction(), min->getDefence());
    } else if(cardName == "Giant Strength") {
        displayEnchant(x, y, "GS", w, cost);
    } else if(cardName == "Enrage") {
        displayEnchant(x, y, "EN", w, cost);
    } else if(cardName == "Haste") {
        displayEnchant(x, y, "HA", w, cost);
    } else if(cardName == "Magic Fatigue") {
        displayEnchant(x, y, "MF", w, cost);
    } else if(cardName == "Silence") {
        displayEnchant(x, y, "SI",  w, cost);
    } else if(cardName == "Dark Ritual") {
        displayRitual(x, y, "DR", w, cost, rit->getAbilityCost(), rit->getCharge());
    } else if(cardName == "Aura of Power") {
        displayRitual(x, y, "AOF", w, cost, rit->getAbilityCost(), rit->getCharge());
    } else if(cardName == "Standstill") {
        displayRitual(x, y, "SS", w, cost, rit->getAbilityCost(), rit->getCharge());
    } else if(cardName == "White Defence") {
        displayRitual(x, y, "WD", w, cost, rit->getAbilityCost(), rit->getCharge());
    } else {
        displayEmpty(x, y, w);
    }
    
}


void GraphicsDisplay::drawHand(Player * p) {
    w->fillRectangle(0, 0, 500, 500, 0);
    vector<Card *> hand = p->getHand();
    if(hand.size() == 0) {
        cout << "No cards to display" << endl;
    } else {
        int x = 0, y = 0;
        for(auto & ob : hand) {
            displayTheCard(ob, x, y, w);
            x += 100;
        }
    }
}

void GraphicsDisplay::drawBoard(Player * p1, Player * p2) {
    int x = 0, y = 0;
    vector<Card *> p1Ritual = p1->getRitual(), p1Grave = p1->getGrave(), p1Minions = p1->getMinions();
    vector<Card *> p2Ritual = p2->getRitual(), p2Grave = p2->getGrave(), p2Minions = p2->getMinions();
    
    if(p1Ritual.size() == 0) {
        displayEmpty(x, y, w);
    } else {
        displayTheCard(p1Ritual.at(0), x, y, w);
    }
    
    x += 100;
    displayEmpty(x, y, w);
    x += 100;
    displayName(x, y, p1->getMyName(), w, p1->getLife(), p1->getMagic(), 1);
    x += 100;
    displayEmpty(x, y, w);
    x += 100;
    
    if(p1Grave.size() == 0) {
        displayEmpty(x, y, w);
    } else {
        displayTheCard(p1Grave.at(p1Grave.size() - 1), x, y, w);
    }
    
    x = 0;
    y += 100;
    for(auto & ob : p1Minions) {
        displayTheCard(ob, x, y, w);
        x += 100;
    }
    
    int emptySlots = 5 - p1Minions.size();
    
    for(int i = 0; i < emptySlots; i++) {
        displayEmpty(x, y, w);
        x += 100;
    }
    
    x = 0;
    y += 100;
    w->fillRectangle(x, y, 500, 100, 0);
    w->drawBigString(x + 175, y + 70, "Sorcery");
    y += 100;
    x = 0;
    
    for(auto & ob : p2Minions) {
        displayTheCard(ob, x, y, w);
        x += 100;
    }
    
    emptySlots = 5 - p2Minions.size();
    
    for(int i = 0; i < emptySlots; i++) {
        displayEmpty(x, y, w);
        x += 100;
    }
    
    y += 100;
    x = 0;
    if(p2Ritual.size() == 0) {
        displayEmpty(x, y, w);
    } else {
        displayTheCard(p2Ritual.at(0), x, y, w);
    }
    
    x += 100;
    displayEmpty(x, y, w);
    x += 100;
    displayName(x, y, p2->getMyName(), w, p2->getLife(), p2->getMagic(), 2);
    x += 100;
    displayEmpty(x, y, w);
    x += 100;
    
    if(p2Grave.size() == 0) {
        displayEmpty(x, y, w);
    } else {
        displayTheCard(p2Grave.at(p2Grave.size() - 1), x, y, w);
    }
}

void GraphicsDisplay::inspectMinion(Player * p, int minIndex) {
    w->fillRectangle(0, 0, 500, 500, 0);
    vector<Card *> minions = p->getMinions();
    Card * ob;
    Minion * min;
    try {
        ob = (p->getMinions()).at(minIndex - 1);
        min = dynamic_cast<Minion *>(ob);
    } catch (out_of_range) {
        cerr << "Minion index out of range" << endl;
        return;
    }
    
    displayTheCard(ob, 0, 0, w);
    
    vector<Card *> enchants = min->getEnchants();
    int size = enchants.size();
    if(size == 0) {
        return;
    } else {
        int quotient = size / 5;
        int remainder = size % 5;
        int index = 0;
        int y = 100;
        for(int i = 0; i <= quotient; i++) {
            int x = 0;
            if(i != quotient) {
                for(int i = 0 + index; i < index + 5; i++) {
                    displayTheCard(enchants[i], x, y, w);
                    x += 100;
                }
            } else {
                for(int i = 0 + index; i < index + remainder; i++) {
                    displayTheCard(enchants[i], x, y, w);
                    x += 100;
                }
            }
            index += 5;
            y += 100;
        }
    }
}
