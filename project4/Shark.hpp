// Shark.hpp
#ifndef SHARK_HPP
#define SHARK_HPP

#include "Point.hpp" 

class Shark {
private:
    Point position;
    int speed;

public:
    Shark(Point pos);        
    void move();            
    void draw();            
    Point getPosition();    
    void setPosition(const Point& pos); 
};

#endif
