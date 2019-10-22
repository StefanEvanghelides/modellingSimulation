#include "../utils/constants.h"
#include "galaxy.h"
#include <iostream>
#include <cmath>

static size_t galaxyClass = 0;

Galaxy::Galaxy(const Coordinate& galaxyCenter, const size_t nrStars)
{
    id = ++galaxyClass;
    this->galaxyCenter = galaxyCenter;
    for (size_t star_idx = 0; star_idx < nrStars; star_idx++)
    {
        const Star& star = initializeStar(id, galaxyCenter);
        addStar(star);
    }
}

Coordinate getPoint() {
    double x = doubleRand() - 0.5;
    double y = doubleRand() - 0.5;
    double z = doubleRand() - 0.5;

    double mag = sqrt(x*x + y*y + z*z);
    x /= mag; y /= mag; z /= mag;

    double d = doubleRand();
    return Coordinate {x*d, y*d, z*d};
}

const Star initializeStar(const size_t galaxyClass, const Coordinate& galaxyCenter)
{
    // Generate random mass
    double mass = doubleRand() * (MASS_MAX - MASS_MIN) + MASS_MIN;

    Coordinate point = getPoint();

    // Generate random coordinates
    const Coordinate& coord {point.x * UNI_MAX_DEV + galaxyCenter.x,
                             point.y * UNI_MAX_DEV + galaxyCenter.y,
                             point.y * UNI_MAX_DEV + galaxyCenter.z};

    // Generate random direction speed
    const Coordinate& dir {doubleRand() * DIR_MIN_DEV + DIR_MIN,
                           doubleRand() * DIR_MIN_DEV + DIR_MIN,
                           doubleRand() * DIR_MIN_DEV + DIR_MIN};

    return Star {galaxyClass, mass, coord, dir};
}

// Generates floating point numbers between [0.0, 1.0).
double doubleRand() {
  return double(rand()) / (double(RAND_MAX) + 1.0);
}

// Show the galaxy on the standard output
void Galaxy::showGalaxy() const
{
    std::cout << "Showing Galaxy " << galaxyClass << ": " << std::endl;
    for (const Star& star : stars)
    {
        star.showStar();
    }
    std::cout << std::endl;
}
