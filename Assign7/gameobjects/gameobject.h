#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "../functions/position/position.h"
#include <string>

class GameObject {
protected:
    Position position;

    int health;
    int maxHealth;

    std::string name;

    int attack;
public:
    GameObject(Position initialPosition, int maxHealth, int attack, std::string name);

    virtual ~GameObject();

    Position getPosition() const;

    void setPosition(Position position);

    int getHealth() const;

    int getMaxHealth() const;

    int getAttack() const;

    void hurt(int damage);

    std::string getName() const;

    virtual void render() = 0;
};

#endif