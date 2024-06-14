#include "slime.h"
#include <stdlib.h>

#include "../../../functions/AnsiPrint/AnsiPrint.h"

Slime::Slime(Position initialPosition): Enemy(initialPosition, 5, 1, "Slime") {
}

// add your code to implement the Slime class here
Slime::~Slime() {}

Position Slime::nextPosition() {
    Position pos = getPosition();
    int direction = rand() % 4;

    switch (direction) {
        case 0:
            return Position(pos.getX(), pos.getY() - 1); // Move up
            break;
        case 1:
            return Position(pos.getX(), pos.getY() + 1); // Move down
            break;
        case 2:
            return Position(pos.getX() - 1, pos.getY()); // Move left
            break;
        case 3:
            return Position(pos.getX() + 1, pos.getY()); // Move right
            break;
    }
    return pos;
}

void Slime::move(InputState action) {
    Position newPos = nextPosition();
    setPosition(newPos);
}

// render function
void Slime::render() {
    AnsiPrint("==", yellow, green);
}
