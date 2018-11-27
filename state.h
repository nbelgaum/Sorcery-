#ifndef _STATE_H_
#define _STATE_H_

enum class Trigger {Start, End, MinEnter, MinExit};  // used to keep track of the type of trigger
enum class Whose {Mine, Opponent};   // used to keep track of which player's action triggered

struct State {
    Trigger time;
    Whose whose;
};

#endif

