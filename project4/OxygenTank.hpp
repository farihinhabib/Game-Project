// OxygenTank.hpp
#ifndef OXYGENTANK_HPP
#define OXYGENTANK_HPP

#include "Collectible.hpp"

class OxygenTank : public Collectible {
public:
    OxygenTank(const Point& position, int refillAmount);
    int collect() override;
    void draw() override;
    void move() override;
};

#endif
