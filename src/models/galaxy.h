#ifndef _GALAXY_H
#define _GALAXY_H

#include "star.h"
#include <vector>


class Galaxy
{
public:
    Galaxy() = delete;
    Galaxy(const Coordinate& galaxyCenter, const size_t nrStars);
    ~Galaxy() = default;

    std::vector<Star> getStars() const {return stars;}
    void addStar(const Star& star) {stars.emplace_back(star);}

    Coordinate getGalaxyCenter() const {return galaxyCenter;}
    size_t getNrStars() const {return stars.size();}

    void showGalaxy() const;

private:
    size_t id;
    std::vector<Star> stars;
    Coordinate galaxyCenter;
};

// Forward declarations
const Star initializeStar(const size_t galaxyClass, const Coordinate& galaxyCenter);
double doubleRand();


#endif // _GALAXY_H