#include "player.h"
#include "../../controller/enviroment.h"
#include "../../functions/AnsiPrint/AnsiPrint.h"

using namespace PlayerState;

Player::Player(Position initialPosition): GameObject(initialPosition, 20, 2, "Player") {
}

Player::~Player() {}

// Add your code to implement the Player class here.
MoveState Player::move(InputState action) {
    switch (action) {
        case ACTION_UP:
            moveUp();
            break;
        case ACTION_DOWN:
            moveDown();
            break;
        case ACTION_LEFT:
            moveLeft();
            break;
        case ACTION_RIGHT:
            moveRight();
            break;
        default:
            break;
    }
    return MOVE;
}

void Player::moveUp() {
    Position pos = getPosition();
    if (pos.getY() > 0) {
        setPosition(Position(pos.getX(), pos.getY() - 1));
    }
}

void Player::moveDown() {
    Position pos = getPosition();
    if (pos.getY() < GAME_WINDOW_SIZE_Y - 1) {
        setPosition(Position(pos.getX(), pos.getY() + 1));
    }
}

void Player::moveLeft() {
    Position pos = getPosition();
    if (pos.getX() > 0) {
        setPosition(Position(pos.getX() - 1, pos.getY()));
    }
}

void Player::moveRight() {
    Position pos = getPosition();
    if (pos.getX() < GAME_WINDOW_SIZE_X - 1) {
        setPosition(Position(pos.getX() + 1, pos.getY()));
    }
}

void Player::heal(int amount) {
    this->health += amount;
    return;
}

int Player::getHealPower() const {
    return healPower;
}

// render
void Player::render() {
    AnsiPrint("PL", green, blue);
}
