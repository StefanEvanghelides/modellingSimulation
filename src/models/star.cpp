#include "star.h"
#include <sstream>
#include <iomanip>

const std::string Star::exportString() const
{
    std::stringstream ss;
    ss  << std::fixed << std::setprecision(3) << std::setw(10) << coord.x
        << std::fixed << std::setprecision(3) << std::setw(10) << coord.y
        << std::fixed << std::setprecision(3) << std::setw(10) << coord.z
        << std::fixed << std::setprecision(4) << std::setw(10) << dir.x
        << std::fixed << std::setprecision(4) << std::setw(10) << dir.y
        << std::fixed << std::setprecision(4) << std::setw(10) << dir.z
        << std::endl;

    return ss.str();
}

void Star::showStar() const
{
    std::cout << "Star: " << id;
    std::cout << "; Coordinate: ";
    coord.showCoordinate();
    std::cout << "; Direction: ";
    dir.showCoordinate();
    std::cout << ";  M: " << mass << std::endl;
}
