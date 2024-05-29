#include "player.h"
#include "../../controller/enviroment.h"
#include "../../functions/AnsiPrint/AnsiPrint.h"

Player::Player(Position initialPosition): GameObject(initialPosition, 20, 2, "Player") {
}

Player::~Player() {
    
}

MoveState Player::move(Direction direction) {
    setPosition(getPosition() + direction);
    return MOVE;
}

void Player::render() {
    AnsiPrint("PL", green, blue);
}
