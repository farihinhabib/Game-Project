// Collectible.hpp
#ifndef COLLECTIBLE_HPP
#define COLLECTIBLE_HPP

#include "Point.hpp"

class Collectible {
protected:
    Point position;
    int value;

public:
    Collectible(const Point& position, int value);
    virtual ~Collectible() = default;

    Point getPosition() const;
    void setPosition(const Point& position);

    int getValue() const;
    void setValue(int value);

    virtual int collect() = 0;
    virtual void draw() = 0; 
    virtual void move() = 0;
};

#endif
