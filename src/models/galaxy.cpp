#include "../utils/constants.h"
#include "galaxy.h"
#include <iostream>


Galaxy::Galaxy(const Coordinate& galaxyCenter, const size_t nrStars)
{
    this->galaxyCenter = galaxyCenter;
    for (size_t star_idx = 0; star_idx < nrStars; star_idx++)
    {
        const Star& star = initializeStar(galaxyCenter);
        addStar(star);
    }
}

void Galaxy::showGalaxy() const
{
    std::cout << "Showing Galaxy:" << std::endl;
    for (const Star& star : stars)
    {
        std::cout << "Star: ";
        star.showStar();
    }
    std::cout << std::endl;
}

const Star initializeStar(const Coordinate& galaxyCenter)
{
    // Generate random coordinates
    const Coordinate& coord {doubleRand() * UNI_MAX_DEV + galaxyCenter.x,
                             doubleRand() * UNI_MAX_DEV + galaxyCenter.y,
                             doubleRand() * UNI_MAX_DEV + galaxyCenter.z};

    // Generate random mass
    double mass = doubleRand() * (MASS_MAX - MASS_MIN) + MASS_MIN;

    return Star {coord, mass};
}

// Generates floating point numbers between [0.0, 1.0).
double doubleRand() {
  return double(rand()) / (double(RAND_MAX) + 1.0);
}
