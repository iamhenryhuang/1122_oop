#include "slime.h"
#include <stdlib.h>

#include "../../../functions/AnsiPrint/AnsiPrint.h"

Slime::Slime(Position initialPosition): Enemy(initialPosition, 5, 1, "Slime") {
}

Slime::~Slime() {

}

// add your code to implement the Slime class here
Position Slime::nextPosition() {
    Position nextPosition = this->getPosition();
    
    int tempSeed = rand() % 4;
    switch(tempSeed) {
        case 0:
            nextPosition = Position(nextPosition.getX(), nextPosition.getY() + 1);
            break;
        case 1:
            nextPosition = Position(nextPosition.getX(), nextPosition.getY() - 1);
            break;
        case 2:
            nextPosition = Position(nextPosition.getX() + 1, nextPosition.getY());
            break;
        case 3:
            nextPosition = Position(nextPosition.getX() - 1, nextPosition.getY());
            break;
        default:
            break;
    }

    return nextPosition;
}

// render function
void Slime::render() {
    AnsiPrint("==", yellow, green);
}
