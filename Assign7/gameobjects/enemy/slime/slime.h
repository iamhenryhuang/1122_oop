#ifndef SLIME_H
#define SLIME_H

#include "../enemy.h"
#include "../../../gamecore/gamestate.h"
#include "../../../controller/enviroment.h"

using namespace GameState;

class Slime: public Enemy {
public:
    Slime(Position initialPosition);
    ~Slime();
    
    // Complete the Slime class with reference to the Enemy class.

    Position nextPosition();
    void move(InputState action);
    void render();
};

#endif