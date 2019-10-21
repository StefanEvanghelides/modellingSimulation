#ifndef _COORDINATE_H
#define _COORDINATE_H

#include <iostream>

typedef struct Coordinate
{
    double x, y, z;

    Coordinate()
        : x{0.0}, y{0.0}, z{0.0} {}
    Coordinate(double oneValue)
        : x{oneValue}, y{oneValue}, z{oneValue} {}
    Coordinate(double x, double y, double z)
        : x{x}, y{y}, z{z} {}
    Coordinate(const Coordinate& other)
        : x{other.x}, y{other.y}, z{other.z} {}

    void showCoordinate() const
    {
        std::cout << "(" << x << "," << y << "," << z << ")";
    }
    
    Coordinate operator+(const Coordinate &other) const
    {
        return Coordinate { x + other.x, y + other.y, z + other.z };
    }
    
    Coordinate operator-(const Coordinate &other) const
    {
        return Coordinate { x - other.x, y - other.y, z - other.z };
    }

    Coordinate operator*(const double multiplier) const
    {
        return Coordinate { x * multiplier, y * multiplier, z * multiplier };
    }

    Coordinate &operator+=(const Coordinate &other)
    {
        this->x += other.x;
        this->y += other.y;
        this->z += other.z;
        return *this;
    }

    Coordinate &operator-=(const Coordinate &other)
    {
        this->x -= other.x;
        this->y -= other.y;
        this->z -= other.z;
        return *this;
    }

} Coordinate;

// Forward declarations
double distance(const Coordinate& coord1, const Coordinate& coord2);
Coordinate middleCoord(const Coordinate& coord1, const Coordinate& coord2);

#endif // _COORDINATE_H