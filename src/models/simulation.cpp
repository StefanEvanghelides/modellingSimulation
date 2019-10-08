#include "simulation.h"
#include "../utils/constants.h"


void Simulation::run()
{
    std::cout << "Running the simulation!" <<std::endl;
    
    // Combine stars from galaxies
    std::vector<Star> stars1 = galaxy1.getStars();
    std::vector<Star> stars2 = galaxy2.getStars();
    copy (stars1.begin(), stars1.end(), back_inserter(this->stars));
    copy (stars2.begin(), stars2.end(), back_inserter(this->stars));

    // show stars - DUMMY FUNCTION, DELETE THIS
    for (const Star& star : this->stars)
    {
        star.showStar();
    }
}

// Gravitational Force formula
double gravitationalForce(const Star& s1, const Star& s2)
{
    const Coordinate c1 = s1.getCoord();
    const Coordinate c2 = s2.getCoord();
    double r = distance(c1, c2);
    double m1 = s1.getMass();
    double m2 = s2.getMass();

    return G * m1 * m2 / pow(r,2);
}