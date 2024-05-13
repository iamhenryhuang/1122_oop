#ifndef POSITION_H
#define POSITION_H

class Position {
private:
    int positionX;
    int positionY;
public:
    Position(int initialPositionX, int initialPositionY);
    Position();
    ~Position();

    int getX() const;
    int getY() const;

    void setX(int newX);
    void setY(int newY);
    
    // add functions what you need
    Position operator+(const Position& other) const;

    bool operator==(const Position &other) const;
};

#endif
