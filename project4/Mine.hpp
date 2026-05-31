// Mine.hpp
#ifndef MINE_HPP
#define MINE_HPP

#include "Enemy.hpp"

class Mine : public Enemy {
private:
    bool isActive;
    int velocityX;
    int velocityY;

public:
    Mine(const Point& position, int damage);

    void move() override;  
    void draw() override;

    void triggerExplosion();
    bool getIsActive() const;
    void setIsActive(bool active);
};

#endif
