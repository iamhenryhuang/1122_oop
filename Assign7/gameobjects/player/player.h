#ifndef PLAYER_H
#define PLAYER_H

#include "../../gamecore/gamestate.h"
#include "../gameobject.h"
#include "playerstate.h"

using namespace PlayerState;
using namespace GameState;

class Player: public GameObject {
    int healPower = 8;
public:
    Player(Position initialPosition);
    ~Player();

    MoveState move(InputState action);

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    
    // To enhance gameplay, a player healing option has been added.
    void heal(int amount);
    int getHealPower() const;
    
    void render();
};

#endif