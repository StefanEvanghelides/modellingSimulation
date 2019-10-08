#include "star.h"

void Star::showStar() const
{
    std::cout << "Star: " << id;
    std::cout << "; Coordinate: ";
    coord.showCoordinate();
    std::cout << "; Direction: ";
    dir.showCoordinate();
    std::cout << ";  M: " << mass << std::endl;
}
