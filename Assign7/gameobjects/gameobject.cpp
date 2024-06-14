#include "gameobject.h"



// Add your code to implement the GameObject class here.
GameObject::GameObject(Position initialPosition, int maxHealth, int attack, std::string name)
    : position(initialPosition), health(maxHealth), maxHealth(maxHealth), attack(attack), name(name) {}

GameObject::~GameObject() {}

Position GameObject::getPosition() const {
    return position;
}

void GameObject::setPosition(Position position) {
    this->position = position;
}

int GameObject::getHealth() const {
    return health;
}

int GameObject::getMaxHealth() const {
    return maxHealth;
}

int GameObject::getAttack() const {
    return attack;
}

void GameObject::hurt(int damage) {
    health -= damage;
    if (health < 0) {
        health = 0;
    }
}

std::string GameObject::getName() const {
    return name;
}
