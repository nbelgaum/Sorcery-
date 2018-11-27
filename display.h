#ifndef display_h
#define display_h


#include <iostream>
#include <stdio.h>

#include "constants.h"
#include "ascii_graphics.h"
#include "player.h"
#include "card.h"
#include "minion.h"
#include "ritual.h"
#include "spell.h"
#include "ritual.h"
#include "enchantment.h"


void displayBoard(Player * p1, Player * p2);
void displayHand(Player * p);
void inspectMinion(Player * p, int minIndex);


#endif
