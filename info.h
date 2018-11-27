#ifndef _INFO_H_
#define _INFO_H_

#include <string>

enum class Target { Me, Opp };   // used to set the target player for spells and certian enchantments

enum class Type { Spell, Minion, Ritual, Enchantment };  // used to determine the type of the card

struct Info {
    Type t;
    Target target;
    std::string n;
    char index;      // the index of the target player's minion or ritual
    int oldMagic = 0; // return the magic of the player in case action fails
};

#endif
