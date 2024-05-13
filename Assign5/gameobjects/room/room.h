#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <vector>

#include "../../controller/enviroment.h"
#include "../../functions/position/position.h"
#include "roomstate.h"

using namespace RoomState;

class Room {
    private:
        int roomID;
        std::string roomName;
        std::string roomDescription;

        Position playerInitialPosition;

        RoomObject defaultRoomObjectMap[GAME_WINDOW_SIZE_Y][GAME_WINDOW_SIZE_X];

    public:
        Room(RoomData roomData);
        ~Room();

        bool walkable(Position position);

        void render(Position position);
};

#endif
