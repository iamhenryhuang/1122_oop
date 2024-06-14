#ifndef MOVE_H
#define MOVE_H

#include "../gameprocess.h"
#include "../../gameobjects/player/player.h"
#include "../../gameobjects/room/room.h"
#include "../../gamecore/gamestate.h"

class Move: public GameProcessBase {
private:
    Player *player;
    
    Room *room;
    
public:
    Move(Player* player, Room* room);
    ~Move();

    ProcessInfo run(InputState action) override;

    void render() override;
};

#endif