#include "simulation/simulation.h"
#include "octree/octree.h"
#include "utils/constants.h"
#include <iostream>

int main(int argc, char** argv)
{
    // User input - galaxy center
    const Coordinate galaxyCenter1 {200, 500, 500};
    const Coordinate galaxyCenter2 {800, 500, 500};

    // User input - number of stars
    const size_t nrStars1 = 5;
    const size_t nrStars2 = 5;

    // User input - number of iterations
    const size_t iterations = 10;

    Galaxy galaxy1 {galaxyCenter1, nrStars1};
    Galaxy galaxy2 {galaxyCenter2, nrStars2};

    galaxy1.showGalaxy();
    galaxy2.showGalaxy();

    // Show total mass of stars
    double totalMass = 0.0f;
    for (const Star& star : galaxy1.getStars()) totalMass += star.getMass();
    for (const Star& star : galaxy2.getStars()) totalMass += star.getMass();
    std::cout << "Total Mass: " << totalMass << std::endl;

    // Run the simulation
    Simulation simulation(galaxy1, galaxy2, iterations);
    simulation.run();
}