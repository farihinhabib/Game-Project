// OxygenTank.cpp
#include "OxygenTank.hpp"
#include <graphics.h>
#include <cmath>

OxygenTank::OxygenTank(const Point& position, int refillAmount)
    : Collectible(position, refillAmount) {}

int OxygenTank::collect() {
    return value;
}

void OxygenTank::move() {
    position.x -= 2;
    position.y += sin(position.x * 0.05) * 2;

    if (position.y < 20) position.y = 20;
    if (position.y > 460) position.y = 460;
}

void OxygenTank::draw() {
    setcolor(BLUE);
    setfillstyle(SOLID_FILL, BLUE);
    fillellipse(position.x, position.y, 10, 10);

    outtextxy(position.x - 6, position.y - 4, const_cast<char*>("O2"));
}


