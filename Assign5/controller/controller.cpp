#include <iostream>

#include "controller.h"
#include "../gameobjects/room/roomdata.h"
#include "../functions/position/position.h"
#include "../functions/AnsiPrint/AnsiPrint.h"

Controller::Controller() {
    const int defaultRoomIndex = 0;
    currentRoomIndex = defaultRoomIndex;
    RoomData roomData = ROOM_DATA[defaultRoomIndex];

    // initialize class
    rooms[currentRoomIndex] = new Room(roomData);

    Position startPosition(0, 0);
    int initialHealth = 100;
    int initialAttack = 10;    
    player = new Player(startPosition, initialHealth, initialAttack, "PL");

    state = GameProcessState::PROCESS_MOVEMENT;


}

// Add your code to implement the Controller class here.
Controller::~Controller() {
    for (auto &room : rooms) {
        delete room.second;
    }
    delete player;
}

RunningState Controller::run(InputState action) {
    Position currentPosition = player->getPosition();
    Position nextMove = currentPosition;

    switch (action) {
    case ACTION_NONE:
        break;
    case ACTION_UP:
        nextMove.setY(currentPosition.getY() - 1);
        break;
    case ACTION_DOWN:
        nextMove.setY(currentPosition.getY() + 1);
        break;
    case ACTION_LEFT:
        nextMove.setX(currentPosition.getX() - 1);
        break;
    case ACTION_RIGHT:
        nextMove.setX(currentPosition.getX() + 1);
        break;
    case ACTION_PAUSE:
        break;
    case ACTION_CONFIRN:
        break;
    case ACTION_EXIT:
        return RunningState::EXIT;
        break;
    case ACTION_INIT:
        break;
    default:
        break;
    }

    if (rooms[currentRoomIndex]->walkable(nextMove)) {
        player->setPosition(nextMove);
    }

    render();

    return RunningState::PLAY;
}

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
