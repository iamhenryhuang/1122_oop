#include "room.h"
#include "roomdata.h"
#include "../../functions/AnsiPrint/AnsiPrint.h"
#include <cstring>

// read data to the Room class
Room::Room(RoomData data)
    :roomID(data.id), roomName(data.name), roomDescription(data.description), playerInitialPosition(data.playerInitialPosition)
{
    /*for(int y = 0; y < GAME_WINDOW_SIZE_Y; y++) {
        for(int x = 0; x < GAME_WINDOW_SIZE_X; x++) {
            this->defaultRoomObjectMap[y][x] = static_cast<RoomObject>(data.defaultRoomObjectMap[y][x]);
        }
    }*/
    std::memcpy(this->defaultRoomObjectMap, data.defaultRoomObjectMap, sizeof(RoomObject) * GAME_WINDOW_SIZE_Y * GAME_WINDOW_SIZE_X);
}

// add your code to implement the Room class here
Room::~Room() {}

bool Room::walkable(Position position)
{
    switch(this->defaultRoomObjectMap[position.getY()][position.getX()]) {
        case OBJECT_NONE:
            return true;
            break;
        case OBJECT_DOOR:
            return true;
            break;
        case OBJECT_GRASS:
            return false;
            break;
        case OBJECT_ROCK:
            return false;
            break;
        case OBJECT_WALL:
            return false;
            break;
        case OBJECT_WATER:
            return false;
            break;
    }
    return false;
}

// render
void Room::render(Position position) {
    switch(this->defaultRoomObjectMap[position.getY()][position.getX()]) {
        case OBJECT_NONE:
            AnsiPrint("  ", black, black);
            break;
        case OBJECT_DOOR:
            AnsiPrint("DR", yellow, black);
            break;
        case OBJECT_WALL:
            AnsiPrint("██", white, black);
            break;
        case OBJECT_GRASS:
            AnsiPrint("WW", green, black);
            break;
        case OBJECT_ROCK:
            AnsiPrint("▲▲", yellow, black);
            break;
        case OBJECT_WATER:
            if(rand() % 2 == 0) {
                AnsiPrint("~~", cyan, blue);
            } else {
                AnsiPrint("……", cyan, blue);
            }
            break;
    }
}
