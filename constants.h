#ifndef constants_h
#define constants_h

#include <stdio.h>
#include <string>

// Descriptions of cards

// Description of spells
const std::string banishDecsr = "Destroy target minion or ritual";
const std::string unsummonDecsr = "Return target minion to its owner's hand";
const std::string rechargeDecsr = "Your ritual gains 3 charges";
const std::string raiseDecsr = "Resurrect the top minion in your graveyard and set it's defence to 1";
const std::string disenDecsr = "Destroy target minion or ritual";
const std::string blizzardDecsr = "Deal 2 damages to all minions";
const std::string suckerDescr = "Sucks magic of opponent(literally)";    // Bonus Card

// Description of minions
const std::string boneDecsr = "Gain +1/+1 whenever a minion leaves play";
const std::string fireDecsr = "Whenever an opponent's minion enters play, deal 1 damage to it";
const std::string potionDecsr = "at the end of your turn all your minions gain +0/+1";
const std::string noviceDecsr = "Deal 1 damage to target minion";
const std::string apprenticeDecsr = "Summon a 1/1 air elemental";
const std::string masterDecsr = "Summon up to three 1/1 air elemental";

// Description of Enchantments
const std::string hasteDecsr = "Enchanted minion gets +1 action each turn";
const std::string magicDecsr = "Enchanted minion's activated ability cost 2 more";
const std::string silenceDecsr = "Enchanted minion cannot use abilities";

// Description of rituals
const std::string darkDecsr = "At the start of your turn gain +1 magic";
const std::string auracDecsr = "Whenever a minions enters the play under your control, it gains +1/+1";
const std::string standDecsr = "Whenever a minion enters a play destroy it";
const std::string whiteDecsr = "Whenever opponent's minion enters play, your life increaes by the minion's defence";

// Names of cards

// Names of spells
const std::string ba = "Banish";
const std::string un = "Unsummon";
const std::string re = "Recharge";
const std::string dis = "Disenchant";
const std::string rd = "Raise Dead";
const std::string bl = "Blizzard";
const std::string mag = "Mag Sucker";      // Bonus Card

// Names of minions
const std::string ae = "Air Elemental";
const std::string ee = "Earth Elemental";
const std::string bg = "Bone Golem";
const std::string fe = "Fire Elemental";
const std::string ps = "Potion Seller";
const std::string np = "Novice Pyromancer";
const std::string as = "Apprentice Summoner";
const std::string ms = "Master Summoner";

// Names of Enchantments
const std::string gs = "Giant Strength";
const std::string en = "Enrage";
const std::string ha = "Haste";
const std::string mf = "Magic Fatigue";
const std::string si = "Silence";

// Name of rituals
const std::string dr = "Dark Ritual";
const std::string aof = "Aura of Power";
const std::string ss = "Standstill";
const std::string wd = "White Defence";

// Empty string
const std::string emp = "";

#endif


