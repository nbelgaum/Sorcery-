#include "display.h"

using namespace std;

vector<string> getTheCard(Card * ob) {
    vector<string> emptyVector;
    emptyVector.emplace_back("");
    string cardName = ob->getName();
    Ritual * ritual = dynamic_cast<Ritual *>(ob);
    Minion * minion = dynamic_cast<Minion *>(ob);
    Enchantment * enchant = dynamic_cast<Enchantment *>(ob);
   
    if(cardName == "Mag Sucker") {
        return display_spell(mag, ob->getCost(), suckerDescr);
    } else if(cardName == "Banish") {
        return display_spell(ba, ob->getCost(), banishDecsr);
    } else if(cardName == "Unsummon") {
        return display_spell(un, ob->getCost(), unsummonDecsr);
    } else if(cardName == "Recharge") {
        return display_spell(re, ob->getCost(), rechargeDecsr);
    } else if(cardName == "Disenchant") {
        return display_spell(dis, ob->getCost(), disenDecsr);
    } else if(cardName == "Raise Dead") {
        return display_spell(rd, ob->getCost(), raiseDecsr);
    } else if(cardName == "Blizzard") {
        return display_spell(bl, ob->getCost(), blizzardDecsr);
    } else if(cardName == "Air Elemental") {
        return display_minion_no_ability(ae, minion->getCost(), minion->getAttack(), minion->getDefence());
    } else if(cardName == "Earth Elemental") {
        return display_minion_no_ability(ee, minion->getCost(), minion->getAttack(), minion->getDefence());
    } else if(cardName == "Bone Golem") {
        return display_minion_triggered_ability(bg, minion->getCost(), minion->getAttack(), minion->getDefence(), boneDecsr);
    } else if(cardName == "Fire Elemental") {
        return display_minion_triggered_ability(fe, minion->getCost(), minion->getAttack(), minion->getDefence(), fireDecsr);
    } else if(cardName == "Potion Seller") {
        return display_minion_triggered_ability(ps, minion->getCost(), minion->getAttack(), minion->getDefence(), potionDecsr);
    } else if(cardName == "Novice Pyromancer") {
        return display_minion_activated_ability(np, minion->getCost(), minion->getAttack(), minion->getDefence(), minion->getAbilityCost(), noviceDecsr);
    } else if(cardName == "Apprentice Summoner") {
        return display_minion_activated_ability(as, minion->getCost(), minion->getAttack(), minion->getDefence(), minion->getAbilityCost(), apprenticeDecsr);
    } else if(cardName == "Master Summoner") {
        return display_minion_activated_ability(ms, minion->getCost(), minion->getAttack(), minion->getDefence(), minion->getAbilityCost(), masterDecsr);
    } else if(cardName == "Giant Strength") {
        return display_enchantment_attack_defence(gs, enchant->getCost(), "", "+2", "+2");
    } else if(cardName == "Enrage") {
        return display_enchantment_attack_defence(en, enchant->getCost(), "", "*2", "*2");
    } else if(cardName == "Haste") {
        return display_enchantment(ha, enchant->getCost(), hasteDecsr);
    } else if(cardName == "Magic Fatigue") {
        return display_enchantment(mf, enchant->getCost(), magicDecsr);
    } else if(cardName == "Silence") {
        return display_enchantment(si, enchant->getCost(), silenceDecsr);
    } else if(cardName == "Dark Ritual") {
        return display_ritual(dr, ritual->getCost(),ritual->getAbilityCost(), darkDecsr, ritual->getCharge());
    } else if(cardName == "Aura of Power") {
        return display_ritual(aof, ritual->getCost(),ritual->getAbilityCost(), auracDecsr, ritual->getCharge());
    } else if(cardName == "Standstill") {
        return display_ritual(ss, ritual->getCost(),ritual->getAbilityCost(), standDecsr, ritual->getCharge());
    } else if(cardName == "White Defence") {
        return display_ritual(wd, ritual->getCost(),ritual->getAbilityCost(), whiteDecsr, ritual->getCharge());
    }
    return emptyVector;
}


void displayBoard(Player * p1, Player * p2) {
    vector<Card *> p1_ritual = p1->getRitual(), p1_grave = p1->getGrave(), p1_minions = p1->getMinions();
    vector<Card *> p2_ritual = p2->getRitual(), p2_grave = p2->getGrave(), p2_minions = p2->getMinions();
    vector<vector<string>> topPanel, bottomPanel, topMidPanel, bottomMidPanel;
    int outerLoop = CARD_TEMPLATE_BORDER.size();
   
    if(p1_ritual.size() < 1) {
        topPanel.emplace_back(CARD_TEMPLATE_BORDER);
    } else {
        topPanel.emplace_back(getTheCard(p1_ritual[0]));
    }
    
    if(p2_ritual.size() < 1) {
        bottomPanel.emplace_back(CARD_TEMPLATE_BORDER);
    } else {
        bottomPanel.emplace_back(getTheCard(p2_ritual[0]));
    }
    
    topPanel.emplace_back(CARD_TEMPLATE_EMPTY);  bottomPanel.emplace_back(CARD_TEMPLATE_EMPTY);
    topPanel.emplace_back(display_player_card(1, p1->getMyName(), p1->getLife(), p1->getMagic()));
    bottomPanel.emplace_back(display_player_card(2, p2->getMyName(), p2->getLife(), p2->getMagic()));
    topPanel.emplace_back(CARD_TEMPLATE_EMPTY);  bottomPanel.emplace_back(CARD_TEMPLATE_EMPTY);

    if(p1_grave.size() < 1) {
        topPanel.emplace_back(CARD_TEMPLATE_BORDER);
    } else {
        topPanel.emplace_back(getTheCard(p1_grave[p1_grave.size() - 1]));
    }
    
    if(p2_grave.size() < 1) {
        bottomPanel.emplace_back(CARD_TEMPLATE_BORDER);
    } else {
        bottomPanel.emplace_back(getTheCard(p2_grave[p2_grave.size() - 1]));
    }
    
    for(auto & ob : p1_minions) {
        topMidPanel.emplace_back(getTheCard(ob));
    }
    
    int emptySlots = 5 - topMidPanel.size();
    
    for(int i = 0; i < emptySlots; i++) {
        topMidPanel.emplace_back(CARD_TEMPLATE_BORDER);
    }
    
    for(auto & ob : p2_minions) {
        bottomMidPanel.emplace_back(getTheCard(ob));
    }
    
    emptySlots = 5 - bottomMidPanel.size();
    
    for(int i = 0; i < emptySlots; i++) {
        bottomMidPanel.emplace_back(CARD_TEMPLATE_BORDER);
    }
    
    // Start printing
    cout << CENTRE_GRAPHIC[0]  << endl;
    for(int i = 0; i < outerLoop; i++) {
        for(int j = 0; j < 5; j++) {
            if(j == 0) {
                cout << EXTERNAL_BORDER_CHAR_UP_DOWN << topPanel[j][i];
            } else if( j != 4) {
                cout << topPanel[j][i];
            } else {
                cout << topPanel[j][i] << EXTERNAL_BORDER_CHAR_UP_DOWN << endl;
            }
        }
    }
    
    cout << MID_BORDER << endl;
    
    for(int i = 0; i < outerLoop; i++) {
        for(int j = 0; j < 5; j++) {
            if(j == 0) {
                cout << EXTERNAL_BORDER_CHAR_UP_DOWN << topMidPanel[j][i];
            } else if( j != 4) {
                cout << topMidPanel[j][i];
            } else {
                cout << topMidPanel[j][i] << EXTERNAL_BORDER_CHAR_UP_DOWN << endl;
            }
        }
    }
    
    cout << MID_BORDER << endl;
    for(auto & ob : CENTRE_GRAPHIC) {
        cout << ob << endl;
    }
    cout << MID_BORDER << endl;
    
    for(int i = 0; i < outerLoop; i++) {
        for(int j = 0; j < 5; j++) {
            if(j == 0) {
                cout << EXTERNAL_BORDER_CHAR_UP_DOWN << bottomMidPanel[j][i];
            } else if( j != 4) {
                cout << bottomMidPanel[j][i];
            } else {
                cout << bottomMidPanel[j][i] <<  EXTERNAL_BORDER_CHAR_UP_DOWN << endl;
            }
        }
    }
    
    cout << MID_BORDER << endl;
    
    for(int i = 0; i < outerLoop; i++) {
        for(int j = 0; j < 5; j++) {
            if(j == 0) {
                cout << EXTERNAL_BORDER_CHAR_UP_DOWN  << bottomPanel[j][i];
            } else if( j != 4) {
                cout << bottomPanel[j][i];
            } else {
                cout << bottomPanel[j][i]  << EXTERNAL_BORDER_CHAR_UP_DOWN << endl;
            }
        }
    }
   
    cout << MID_BORDER << endl;
    cout << CENTRE_GRAPHIC[0]  << endl;

}


void displayHand(Player * p) {
    vector<vector<string>> handStrings;
    vector<Card *> hand = p->getHand();
    for(auto & ob : hand) {
        handStrings.emplace_back(getTheCard(ob));

    }
    
    if(handStrings.size() <= 0) {
        cout << "No cards in hand to display" << endl;
        return;
    }
    
    int outerLoopSize = handStrings[0].size();
    int innerLoopSize = handStrings.size();
    
    for(int i = 0; i < outerLoopSize; i++) {
        for(int j = 0; j < innerLoopSize; j++) {
            if(j != innerLoopSize - 1) {
                cout << handStrings[j][i] << " ";
            } else {
                cout << handStrings[j][i] << endl;
            }
        }
    }
}


void inspectMinion(Player * p, int minIndex) {
    vector<Card *> minions = p->getMinions();
    Card * ob;
    try {
     ob = minions.at(minIndex - 1);
    } catch (out_of_range) {
       cerr << "Minion out of range" << endl;
       return;
   }
    vector<vector<string>> enchantStrings;
    vector<string> minString = getTheCard(ob);
    for(auto & ob : minString) {
        cout << ob << endl;
    }
    Minion * minion = dynamic_cast<Minion *>(ob);
    vector <Card *> enchants = minion->getEnchants();
    for(auto & ob : enchants) {
        enchantStrings.emplace_back(getTheCard(ob));
    }
    
    if(enchantStrings.size() <= 0) {
        return;
    }
    
    int sizeOfEnchants = enchantStrings.size();
    int quotient = sizeOfEnchants/5;
    int remainder = sizeOfEnchants % 5;
    int outerLoopSize = enchantStrings[0].size();
    int index = 0;
    for(int i = 0; i <= quotient; i++) {
        for(int j = 0; j < outerLoopSize; j++) {
            if(i != quotient) {
                for(int k = 0 + index; k < 5 + index; k++) {
                    if(k != 5 + index - 1) {
                        cout << enchantStrings[k][j] << " ";
                    } else {
                        cout << enchantStrings[k][j] << endl;
                    }
                }
            } else {
                for(int k = 0 + index; k < index + remainder; k++) {
                    if(k != index + remainder - 1) {
                        cout << enchantStrings[k][j] << " ";
                    } else {
                        cout << enchantStrings[k][j] << endl;
                    }
                }
            }
        }
      index += 5;
    }
}

