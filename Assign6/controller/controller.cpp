#include <iostream>

#include "controller.h"
#include "../gameobjects/room/roomdata.h"
#include "../functions/position/position.h"
#include "../functions/AnsiPrint/AnsiPrint.h"

Controller::Controller() {
    const int defaultRoomIndex = 0;
    RoomData roomData = ROOM_DATA[defaultRoomIndex];

    // initialize class
    player = new Player(roomData.playerInitialPosition);
    int index = 0;
    for (const auto& roomData : ROOM_DATA) {
        rooms[index++] = new Room(roomData);
    }
    currentRoomIndex = defaultRoomIndex;
    state = PROCESS_MOVEMENT;    
}

Controller::~Controller() {
    for (size_t i = 0; i < rooms.size(); i++) {
        delete rooms[i];
    }
    delete player;
}

Direction InputStateToDirection(InputState input) {
    switch(input) {
    case ACTION_UP:
        return DIRECTION_UP;
    case ACTION_DOWN:
        return DIRECTION_DOWN;
    case ACTION_LEFT:
        return DIRECTION_LEFT;
    case ACTION_RIGHT:
        return DIRECTION_RIGHT;
    default:
        return DIRECTION_NONE;
    }
}

RunningState Controller::run(InputState action) {

    switch (state) {
    case PROCESS_MOVEMENT: {
        
        // add your code to implement the enemy movement
        Direction direction = InputStateToDirection(action);
        Position nextPosition = player->getPosition() + direction;

        // Check boundary conditions and handle room switching
        if (direction == DIRECTION_LEFT && player->getPosition().getX() == 0) {
            if (currentRoomIndex > 0) {
                currentRoomIndex--;
                nextPosition.setX(GAME_WINDOW_SIZE_X - 1); // Move to the rightmost position of the new room
            }
        } else if (direction == DIRECTION_RIGHT && player->getPosition().getX() == GAME_WINDOW_SIZE_X - 1) {
            if (currentRoomIndex < rooms.size() - 1) {
                currentRoomIndex++;
                nextPosition.setX(0); // Move to the leftmost position of the new room
            }
        } 

        // Check boundary conditions for Y axis
        if (nextPosition.getY() < 0) {
            nextPosition.setY(0);
        }
        if (nextPosition.getY() >= GAME_WINDOW_SIZE_Y) {
            nextPosition.setY(GAME_WINDOW_SIZE_Y - 1);
        }

        // Check if the next position is walkable in the current room
        if (rooms[currentRoomIndex]->walkable(nextPosition)) {
            player->setPosition(nextPosition);
        }


        for (auto enemy : rooms[currentRoomIndex]->getEnemies()) {
            Position enemyNextPosition = enemy->nextPosition();
                
            if (rooms[currentRoomIndex]->walkable(enemyNextPosition)) {
                enemy->setPosition(enemyNextPosition);
            }
        }


        break;
    }

    default:
        break;
    }

    this->render();

    return PLAY;
}

// Add your code to implement the Controller class here.

/*void Controller::roomChange(int roomIndex) {
    currentRoomIndex = roomIndex;
}*/

// render
void Controller::render() {
    switch (state) {
    case PROCESS_MOVEMENT:{
        for (int y = 0; y < GAME_WINDOW_SIZE_Y; y++) {
            for (int x = 0; x < GAME_WINDOW_SIZE_X; x++) {
                if(player->getPosition() == Position(x, y)) {
                    player->render();
                    continue;
                }
                bool flag = false;
                for(auto enemy : rooms[currentRoomIndex]->getEnemies()) {
                    if(enemy->getPosition() == Position(x, y)) {
                        enemy->render();
                        flag = true;
                        continue;
                    }
                }
                if(flag) continue;
                rooms[currentRoomIndex]->render(Position(x, y));
            }
            AnsiPrint("\n", nochange, nochange);
        }
        break;
    }
    
    default:
        break;
    }
    output();
}
