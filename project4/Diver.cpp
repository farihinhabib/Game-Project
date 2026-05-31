// Diver.cpp
#include "Diver.hpp"
#include <graphics.h>
#include <iostream>

Diver::Diver(const Point& startPosition, int health, int oxygen)
    : position(startPosition), health(health), oxygenLevel(oxygen), score(0) {}

int Diver::getHealth() const { return health; }
void Diver::setHealth(int h) { 
    if (h > 100) h = 100;
    if (h < 0) h = 0;
    health = h; 
}

int Diver::getOxygenLevel() const { return oxygenLevel; }
void Diver::setOxygenLevel(int o) { 
    if (o > 100) o = 100;
    if (o < 0) o = 0;
    oxygenLevel = o; 
}

int Diver::getTime() const { return time; }
void Diver::setTime(int t) {
    time = (t >= 0) ? t : 0;
}

int Diver::getScore() const { return score; }
void Diver::setScore(int s) { score = s; }

void Diver::setSpeed(int s) {
    if (s > 0) speed = s;
}

int Diver::getSpeed() const {
    return speed;
}

Point Diver::getPosition() const { return position; }
void Diver::setPosition(const Point& pos) { position = pos; }

void Diver::move(const std::string& direction) {
    const int diverSize = 25; 
    const int screenWidth = 800;
    const int screenHeight = 400;

    int newX = position.x;
    int newY = position.y;

    if (direction == "up") newY -= speed;
    else if (direction == "down") newY += speed;
    else if (direction == "left") newX -= speed;
    else if (direction == "right") newX += speed;

    if (newX - diverSize / 2 >= 0 && newX + diverSize / 2 <= screenWidth)
        position.x = newX;

    if (newY - diverSize / 2 >= 50 && newY + diverSize / 200 <= screenHeight)
        position.y = newY;
}

void Diver::takeDamage(int amount) {
    health -= amount;
    if (health < 0) health = 0;
}

void Diver::updateOxygen() {
    oxygenLevel -= 1;
    if (oxygenLevel < 0) oxygenLevel = 0;
}

void Diver::draw() const {
    readimagefile("diver.bmp", position.x + 25, position.y + 25, position.x - 25, position.y - 25);
}

