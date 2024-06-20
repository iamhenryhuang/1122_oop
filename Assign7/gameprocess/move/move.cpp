#include "move.h"
#include "../../functions/AnsiPrint/AnsiPrint.h"
#include "../../controller/enviroment.h"

// Move the code from controller.cpp to this file, completing the Move Class
Move::Move(Player* player, Room* room) : player(player), room(room) {}

Move::~Move() {}

ProcessInfo Move::run(InputState action) {
    // implement movement logic here
    Position pos = player->getPosition();
    int pos_x = pos.getX();
    int pos_y = pos.getY();
    switch (action) {
        case ACTION_UP:
            if (room->walkable({pos_x, pos_y - 1})) {
                player->moveUp();
            }
            break;
        case ACTION_DOWN:
            if (room->walkable({pos_x, pos_y + 1})) {
                player->moveDown();
            }
            break;
        case ACTION_LEFT:
            if (pos_x > 0 && room->walkable({pos_x - 1, pos_y})) {
                if (pos_x == 0){
                    player->setPosition(Position(GAME_WINDOW_SIZE_X - 1, pos_y));
                    return MOVE_FINISH_ROOMCHANGE_LEFT;
                }
                player->moveLeft();
            }
            break;
        case ACTION_RIGHT:
            if (pos_x < GAME_WINDOW_SIZE_X && room->walkable({pos_x + 1, pos_y})) {
                if (pos_x == GAME_WINDOW_SIZE_X - 1){
                    player->setPosition(Position(0, pos_y));
                    return MOVE_FINISH_ROOMCHANGE_RIGHT;
                }
                player->moveRight();
            }
            break;
        case ACTION_PAUSE:
            return MOVE_FINISH_PAUSE;
        case ACTION_BATTLE:
            return MOVE_FINISH_BATTLE;
        default:
            break;
    }

    for (auto enemy : room->getEnemies()) {
        Position enemyNextPosition = enemy->nextPosition();
                
        if (room->walkable(enemyNextPosition)) {
            enemy->setPosition(enemyNextPosition);
        }
    }

    for(auto enemy : room->getEnemies()) {
        if(enemy->getPosition() == player->getPosition()) {
            return MOVE_FINISH_BATTLE;
        }
    }
    
    return CONTINUE;
}

void Move::render() {
    for (int y = 0; y < GAME_WINDOW_SIZE_Y; y++) {
        for (int x = 0; x < GAME_WINDOW_SIZE_X; x++) {
            if(player->getPosition() == Position(x, y)) {
                player->render();
                continue;
            }
            bool flag = false;
            for(auto enemy : room->getEnemies()) {
                if(enemy->getPosition() == Position(x, y)) {
                    enemy->render();
                    flag = true;
                    continue;
                }
            }
            if(flag) continue;
            room->render(Position(x, y));
        }
    AnsiPrint("\n", nochange, nochange);
    }
}
