#include "player.h"
#include "../../controller/enviroment.h"
#include "../../functions/AnsiPrint/AnsiPrint.h"

using namespace PlayerState;

// Add your code to implement the Player class here.
Player::Player(Position initialPosition, int maxHealth, int attack, std::string name)
    : GameObject(initialPosition, maxHealth, attack, name)
{

}

void Player::move(char direction) {
    Position pos = getPosition();
    switch (direction) {
        case 'W': 
            setPosition(Position(pos.getX(), pos.getY() - 1)); 
            break;
        case 'S': 
            setPosition(Position(pos.getX(), pos.getY() + 1)); 
            break;
        case 'A': 
            setPosition(Position(pos.getX() - 1, pos.getY())); 
            break;
        case 'D': 
            setPosition(Position(pos.getX() + 1, pos.getY())); 
            break;
        default:
            break;
    }
}



// render
void Player::render() {
    AnsiPrint("PL", green, blue);
}
