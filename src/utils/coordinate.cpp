#include "coordinate.h"
#include <cmath>

// Distance formula
double distance(const Coordinate& coord1, const Coordinate& coord2)
{
    double dist = sqrt(pow(coord1.x - coord2.x, 2) +
                       pow(coord1.y - coord2.y, 2) +
                       pow(coord1.z - coord2.z, 2));
    
    return dist;
}

// Middle coordinate formula
Coordinate middleCoord(const Coordinate& coord1, const Coordinate& coord2)
{
    double midX = (coord1.x + coord2.x) / 2;
    double midY = (coord1.y + coord2.y) / 2;
    double midZ = (coord1.z + coord2.z) / 2;

    return Coordinate {midX, midY, midZ};
}
