// Shark.cpp
#include "Shark.hpp"
#include <graphics.h>

const int SAFE_ZONE_TOP = 180;
const int SAFE_ZONE_BOTTOM = 420;

Shark::Shark(Point pos) : position(pos), speed(5) {}

void Shark::move() {
    position.x -= speed;

    if (position.x < -50) {
        position.x = 840 + rand() % 200;
        position.y = SAFE_ZONE_TOP + rand() % (SAFE_ZONE_BOTTOM - SAFE_ZONE_TOP + 1);
    }

    if (position.y < SAFE_ZONE_TOP) position.y = SAFE_ZONE_TOP;
    if (position.y > SAFE_ZONE_BOTTOM) position.y = SAFE_ZONE_BOTTOM;
}

void Shark::draw() {
    readimagefile("shark.bmp", position.x, position.y, position.x + 60, position.y + 40);
}

Point Shark::getPosition() {
    return position;
}

void Shark::setPosition(const Point& pos) {
    int clampedY = std::max(SAFE_ZONE_TOP, std::min(pos.y, SAFE_ZONE_BOTTOM - 40));
    position = Point(pos.x, clampedY);
}

