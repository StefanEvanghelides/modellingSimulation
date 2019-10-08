#include "star.h"

void Star::showStar() const
{
    std::cout << "Coordinate: ";
    coord.showCoordinate();
    std::cout << ";  M: " << mass << std::endl;
}
