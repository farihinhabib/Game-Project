// TreasureChest.cpp
#include "TreasureChest.hpp"
#include <graphics.h>
#include <cmath>

const int SAFE_ZONE_TOP = 180;
const int SAFE_ZONE_BOTTOM = 420;

TreasureChest::TreasureChest(const Point& position, int value)
    : Collectible(position, value) {}

int TreasureChest::collect() {
    return value;
}

void TreasureChest::move() {
    position.x -= 2;
    position.y += cos(position.x * 0.03) * 2;

    if (position.y < SAFE_ZONE_TOP) position.y = SAFE_ZONE_TOP;
    if (position.y > SAFE_ZONE_BOTTOM) position.y = SAFE_ZONE_BOTTOM;
}

void TreasureChest::draw() {
    setcolor(YELLOW);
    setfillstyle(SOLID_FILL, YELLOW);
    fillellipse(position.x, position.y, 12, 12);
    outtextxy(position.x - 4, position.y - 4, const_cast<char*>("$"));
}