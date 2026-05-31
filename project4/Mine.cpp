// Mine.cpp
#include "Mine.hpp"
#include <graphics.h>

const int SAFE_ZONE_TOP = 180;
const int SAFE_ZONE_BOTTOM = 420;

Mine::Mine(const Point& position, int damage)
    : Enemy(position, damage), isActive(true) {

    velocityX = -(rand() % 3 + 1);
    velocityY = (rand() % 2 == 0) ? -1 : 1;
}

void Mine::move() {
    if (!isActive) return;

    position.x += velocityX;
    position.y += velocityY;

    if (position.y <= SAFE_ZONE_TOP || position.y >= SAFE_ZONE_BOTTOM){
        velocityY = -velocityY;
        if (position.y < SAFE_ZONE_TOP) position.y = SAFE_ZONE_TOP;
        if (position.y > SAFE_ZONE_BOTTOM) position.y = SAFE_ZONE_BOTTOM;
    }
}

void Mine::draw() {
    if (!isActive) return;
    readimagefile("mine.bmp", position.x - 15, position.y - 15, position.x + 15, position.y + 15);
}

void Mine::triggerExplosion() {
    isActive = false;
}

bool Mine::getIsActive() const {
    return isActive;
}

void Mine::setIsActive(bool active) {
    isActive = active;
}
