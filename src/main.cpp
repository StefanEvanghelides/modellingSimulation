#include "simulation/simulation.h"
#include "octree/octree.h"
#include "utils/constants.h"
#include <iostream>

int main(int argc, char** argv)
{
    // User input - galaxy center
    const Coordinate galaxyCenter1 {200, 500, 500};
    const Coordinate galaxyCenter2 {800, 500, 500};

    size_t nrStars1 = 1000;
    size_t nrStars2 = 1000;
    size_t iterations = 100;

    // User input - number of stars
    // User input - number of iterations
    if (argc > 1)
    {
        nrStars1 = atoi(argv[1]);
        nrStars2 = atoi(argv[2]);
        iterations = atoi(argv[3]);
    }

    Galaxy galaxy1 {galaxyCenter1, nrStars1};
    Galaxy galaxy2 {galaxyCenter2, nrStars2};

    // Show galaxies for debbuging purposes
    //galaxy1.showGalaxy();
    //galaxy2.showGalaxy();

    // Show total mass of stars
    double totalMass = 0.0f;
    for (const Star& star : galaxy1.getStars()) totalMass += star.getMass();
    for (const Star& star : galaxy2.getStars()) totalMass += star.getMass();
    std::cout << "Total Mass: " << totalMass << std::endl;

    // Run the simulation
    Simulation simulation(galaxy1, galaxy2, iterations);
    simulation.run();
}