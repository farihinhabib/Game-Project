// TreasureChest.hpp
#ifndef TREASURECHEST_HPP
#define TREASURECHEST_HPP

#include "Collectible.hpp"

class TreasureChest : public Collectible {
public:
    TreasureChest(const Point& position, int value);
    int collect() override;
    void draw() override;
    void move() override;
};

#endif