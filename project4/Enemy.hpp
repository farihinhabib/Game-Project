// Enemy.hpp
#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Point.hpp"

class Enemy {
protected:
    Point position;
    int damage;

public:
    Enemy(const Point& position, int damage);
    virtual ~Enemy() = default;

    Point getPosition() const;
    void setPosition(const Point& position);

    int getDamage() const;
    void setDamage(int damage);

    virtual void move() = 0;
    virtual void draw() = 0;
};

#endif
