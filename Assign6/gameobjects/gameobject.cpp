#include "gameobject.h"

// Add your code to implement the GameObject class here.
GameObject::GameObject(Position initialPosition, int health, int attack, std::string name) 
    : maxHealth(health), attack(attack) {
    position = initialPosition;
    this->health = health;
    this->name = name;
}

GameObject::~GameObject() {
}

Position GameObject::getPosition() {
    return position;
}

void GameObject::setPosition(Position position) {
    this->position = position;
}

/*int GameObject::getHealth() {
    return health;
}*/

/*int GameObject::getMaxHealth() {
    return maxHealth;
}*/

/*int GameObject::getAttack() {
    return attack;
}*/

/*void GameObject::hurt(int damage) {
    health -= damage;
    if(health < 0) {
        health = 0;
    }
}*/

std::string GameObject::getName() {
    return name;
}
