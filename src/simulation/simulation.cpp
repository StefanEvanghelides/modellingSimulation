#include "simulation.h"
#include "../utils/constants.h"
#include <sstream>

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

    for (size_t iter = 0; iter < iterations; iter++)
    {
        update(iter);
    }
}

void Simulation::update(size_t iteration)
{
    for (Star& star : stars)
    {
        for (Star& other : stars)
        {
            if (star == other) continue; // skip the same star

            // DO something here
            // Update stars
        }
    }
    exportIteration(iteration);
}

void Simulation::exportIteration(size_t iteration)
{
    // Generate the name of the file
    const std::string& fileName = getFileName(iteration);

    // Export to file
}

std::string Simulation::getFileName(size_t iteration)
{
    const size_t nrStars1 = galaxy1.getNrStars();
    const size_t nrStars2 = galaxy2.getNrStars();

    std::stringstream ss;
    ss  << nrStars1 << "-by-" << nrStars2
        << "_iterations=" << this->iterations
        << "_step=" << iteration;

    return ss.str();
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