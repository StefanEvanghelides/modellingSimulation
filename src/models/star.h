#ifndef _STAR_H
#define _STAR_H

#include "../utils/coordinate.h"
#include <cmath>

class Star
{
public:
    Star() = delete;
    Star(const Coordinate& coord, double mass)
        : coord{coord}, mass{mass} {};
    ~Star() = default;

    Coordinate getCoord() const {return coord;}
    double getMass() const {return mass;}

    void showStar() const;

private:
    Coordinate coord;
    double mass;
};

#endif // _STAR_H