// Enemy.cpp
#include "Enemy.hpp"

Enemy::Enemy(const Point& position, int damage)
    : position(position), damage(damage) {}

Point Enemy::getPosition() const {
    return position;
}

void Enemy::setPosition(const Point& position) {
    this->position = position;
}

int Enemy::getDamage() const {
    return damage;
}

void Enemy::setDamage(int damage) {
    this->damage = damage;
}
