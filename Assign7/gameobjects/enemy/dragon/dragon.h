#ifndef DRAGON_H
#define DRAGON_H

#include "../enemy.h"
#include "../../../gamecore/gamestate.h"
#include "../../../controller/enviroment.h"

using namespace GameState;

class Dragon: public Enemy {
public:
    Dragon(Position initialPosition, bool isLastBoss = false);
    ~Dragon();

    // Complete the Dragon class with reference to the Enemy class.
    Position nextPosition();
    void move(InputState action);
    void render();
};

#endif