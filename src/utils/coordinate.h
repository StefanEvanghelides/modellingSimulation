#ifndef _COORDINATE_H
#define _COORDINATE_H

#include <iostream>

typedef struct Coordinate
{
    double x, y, z;

    Coordinate()
        : x{0}, y{0}, z{0} {}
    Coordinate(double oneValue)
        : x{oneValue}, y{oneValue}, z{oneValue} {}
    Coordinate(double x, double y, double z)
        : x{x}, y{y}, z{z} {}

    void showCoordinate() const
    {
        std::cout << "(" << x << "," << y << "," << z << ")";
    }

    // static Coordinate middleCoord(const Coordinate& coord1, const Coordinate& coord2);

} Coordinate;

// Forward declarations
double distance(const Coordinate& coord1, const Coordinate& coord2);
Coordinate middleCoord(const Coordinate& coord1, const Coordinate& coord2);

#endif // _COORDINATE_H