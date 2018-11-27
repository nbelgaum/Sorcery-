#ifndef GRAPHICSDISPLAY_H
#define GRAPHICSDISPLAY_H

#include <iostream>
#include <string>

#include "window.h"
#include "constants.h"
#include "player.h"
#include "card.h"
#include "minion.h"
#include "ritual.h"
#include "spell.h"
#include "ritual.h"
#include "enchantment.h"

class GraphicsDisplay {
    
    Xwindow * w;
    
    public :
    GraphicsDisplay();
    ~GraphicsDisplay();
    void drawHand(Player * p);
    void drawBoard(Player * p1, Player * p2);
    void inspectMinion(Player * p, int minIndex);
    
};



#endif /* graphicsdisplay_hpp */

