#include "star.h"
#include <sstream>
#include <iomanip>

const std::string Star::exportString() const
{
    std::stringstream ss;
    ss  << "    " << galaxyClass << " ;"
        << std::fixed << std::setprecision(3) << coord.x << ';'
        << std::fixed << std::setprecision(3) << coord.y << ';'
        << std::fixed << std::setprecision(3) << coord.z << ';'
        << std::fixed << std::setprecision(4) << dir.x << ';'
        << std::fixed << std::setprecision(4) << dir.y << ';'
        << std::fixed << std::setprecision(4) << dir.z << ';'
        << std::endl;

    return ss.str();
}

void Star::showStar() const
{
    std::cout << "Star: " << id;
    std::cout << "; Galaxy class: " << galaxyClass;
    std::cout << "; Coordinate: ";
    coord.showCoordinate();
    std::cout << "; Direction: ";
    dir.showCoordinate();
    std::cout << ";  M: " << mass << std::endl;
}

void Star::printCenterOfMassWith(const Star &other)
{
    double m = mass + other.getMass();
    Coordinate otherCoord = other.getCoord();
    double otherMass = other.getMass();

    double newX = (coord.x * mass + otherCoord.x * otherMass) / m;
    double newY = (coord.y * mass + otherCoord.y * otherMass) / m;
    double newZ = (coord.z * mass + otherCoord.z * otherMass) / m;

    coord = Coordinate { newX, newY, newZ };
    std::cout << "{ " << coord.x << ", " << coord.y << ", " << coord.z << " }\n";
}