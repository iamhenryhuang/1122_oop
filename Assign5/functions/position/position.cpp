#include "position.h"
#include "../../controller/enviroment.h"

// Add your code to implement the Position class here.
Position::Position() : positionX(0), positionY(0) {};

Position::Position(int x, int y) : positionX(x), positionY(y) {};

Position::~Position() {};

int Position::getX() const {
    return positionX;
}

int Position::getY() const {
    return positionY;
}

void Position::setX(int newX) {
    positionX = newX;
}

void Position::setY(int newY) {
    positionY = newY;
}

Position Position::operator+(const Position& other) const {
    return Position(positionX + other.positionX, positionY + other.positionY);
}

bool Position::operator==(const Position& other) const {
    return (positionX == other.getX()) && (positionY == other.getY());
}
