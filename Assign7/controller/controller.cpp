#include <iostream>

#include "controller.h"
#include "../gameobjects/room/roomdata.h"
#include "../functions/position/position.h"
#include "../functions/AnsiPrint/AnsiPrint.h"

#include "../gameprocess/allgameprocess.h"

Controller::Controller() {
    const int defaultRoomIndex = 0;
    RoomData roomData = ROOM_DATA[defaultRoomIndex];
    Room *room = new Room(roomData);
    rooms.insert(std::pair<int, Room *>(defaultRoomIndex, room));
    currentRoomIndex = defaultRoomIndex;
    player = new Player(roomData.playerInitialPosition);

    state = PROCESS_MOVEMENT;
    currentProcess = new Move(player, room);
}

Controller::~Controller() {
    for (size_t i = 0; i < rooms.size(); i++) {
        delete rooms[i];
    }
    delete player;
}

RunningState Controller::run(InputState action) {

    if(state == PROCESS_GAMEOVER) {
        return EXIT;
    }

    if(state == PROCESS_GAMECLEAR) {
        return EXIT;
    }

    ProcessInfo info = currentProcess->run(action);

    // add your code to implement process control
    switch(info) {
        case MOVE_FINISH_ROOMCHANGE_LEFT:
            roomChangeLeft();
            break;
        case MOVE_FINISH_ROOMCHANGE_RIGHT:
            roomChangeRight();
            break;
        case MOVE_FINISH_PAUSE:
            delete currentProcess;
            currentProcess = new Pause();
            state = PROCESS_PAUSE;
            break;
        case MOVE_FINISH_BATTLE:
            state = PROCESS_BATTLE;
            delete currentProcess;
            currentProcess = new Battle(player, rooms[currentRoomIndex]->getEnemies()[0]);
            break;
        case BATTLE_FINISH_PLAYER_WIN:
            state = PROCESS_MOVEMENT;
            delete currentProcess;
            currentProcess = new Move(player, rooms[currentRoomIndex]);
            break;
        case BATTLE_FINISH_PLAYER_DEAD:
            state = PROCESS_GAMEOVER;
            delete currentProcess;
            currentProcess = new GameOver();
            break;
        case PAUSE_FINISH:
            state = PROCESS_MOVEMENT;
            delete currentProcess;
            currentProcess = new Move(player, rooms[currentRoomIndex]);
            break;
        default:
            break;
    }

    this->render();

    return PLAY;
}

// Add your code to implement the Controller class here.
void Controller::roomChangeLeft() {
    currentRoomIndex--;
    if (rooms.find(currentRoomIndex) == rooms.end()) {
        RoomData roomData = ROOM_DATA[currentRoomIndex];
        rooms[currentRoomIndex] = new Room(roomData);
    }
    delete currentProcess;
    currentProcess = new Move(player, rooms[currentRoomIndex]);
}

void Controller::roomChangeRight() {
    currentRoomIndex++;
    if (rooms.find(currentRoomIndex) == rooms.end()) {
        RoomData roomData = ROOM_DATA[currentRoomIndex];
        rooms[currentRoomIndex] = new Room(roomData);
    }
    delete currentProcess;
    currentProcess = new Move(player, rooms[currentRoomIndex]);
}

// render
void Controller::render() {
    currentProcess->render();
    output();
}
