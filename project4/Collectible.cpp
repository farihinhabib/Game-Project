// Collectible.cpp
#include "Collectible.hpp"
#include <algorithm>

const int SAFE_ZONE_TOP = 180;
const int SAFE_ZONE_BOTTOM = 420;

Collectible::Collectible(const Point& position, int value) : position(position), value(value) {}

Point Collectible::getPosition() const {
    return position;
}

void Collectible::setPosition(const Point& pos) {
    int clampedY = std::max(SAFE_ZONE_TOP, std::min(pos.y, SAFE_ZONE_BOTTOM));
    this->position = Point(pos.x, clampedY);
}

int Collectible::getValue() const {
    return value;
}

void Collectible::setValue(int value) {
    this->value = value;
}
