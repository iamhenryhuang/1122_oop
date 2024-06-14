#include "position.h"
#include "../../controller/enviroment.h"

// Add your code to implement the Position class here.
#include "position.h"

Position::Position(int initialPositionX, int initialPositionY) : positionX(initialPositionX), positionY(initialPositionY) {}

Position::Position() : positionX(0), positionY(0) {}

Position::~Position() {}

int Position::getX() const{
    return positionX;
}

int Position::getY() const {
    return positionY;
}

bool Position::operator==(const Position &other) const {
    return positionX == other.positionX && positionY == other.positionY;
}
