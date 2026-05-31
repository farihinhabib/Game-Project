// Diver.hpp
#ifndef DIVER_HPP
#define DIVER_HPP

#include "Point.hpp"
#include <string>

class Diver {
private:
    int health;
    int time = 180;
    int oxygenLevel;
    int score;
    int speed;
    Point position;

public:
    Diver(const Point& startPosition, int health = 100, int oxygen = 100);

    // Getters and setters
    int getHealth() const;
    void setHealth(int health);

    int getOxygenLevel() const;
    void setOxygenLevel(int oxygen);

    int getTime() const;
    void setTime(int t);

    int getScore() const;
    void setScore(int score);

    int getSpeed() const;
    void setSpeed(int s);

    Point getPosition() const;
    void setPosition(const Point& pos);

    // Actions
    void move(const std::string& direction);
    void takeDamage(int amount);
    void updateOxygen();

    // Display
    void draw() const;
};

#endif
