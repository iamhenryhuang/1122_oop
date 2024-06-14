#include "enemy.h"

// add your code to implement the Enemy class here
Enemy::Enemy(Position initialPosition, int health, int attack, std::string name)
    : GameObject(initialPosition, health, attack, name), lastBoss(false) {}

Enemy::Enemy(Position initialPosition, int health, int attack, std::string name, bool isLastBoss)
    : GameObject(initialPosition, health, attack, name), lastBoss(isLastBoss) {}

Enemy::~Enemy() {}

bool Enemy::isLastBoss() const {
    return lastBoss;
}

void Enemy::heal(int amount) {
    int newHealth = getHealth() + amount;
    if (newHealth > getMaxHealth()) {
        newHealth = getMaxHealth();
    }
}
