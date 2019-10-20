#include "simulation/simulation.h"
#include "octree/octree.h"
#include "utils/constants.h"
#include <iostream>
#include <cstring>

int main(int argc, char** argv)
{
    // Default galaxy centers
    const Coordinate galaxyCenter1 {200, 500, 500};
    const Coordinate galaxyCenter2 {800, 500, 500};

    // Default user input
    size_t nrStars1 = 1000;
    size_t nrStars2 = 1000;
    size_t iterations = 1000;
    debugMode = false;

    // User input - number of stars
    if (argc > 1) nrStars1 = atoi(argv[1]);
    if (argc > 2) nrStars2 = atoi(argv[2]);
    // User input - number of iterations
    if (argc > 3) iterations = atoi(argv[3]);
    // User input - debugMode
    if (argc > 4 && strnicmp(argv[4], "-d", 2)==0) debugMode = true;

    //
    // --------------------------------------------------------
    // Generate the galaxies
    Galaxy galaxy1 {galaxyCenter1, nrStars1};
    Galaxy galaxy2 {galaxyCenter2, nrStars2};

    // Show galaxies for debbuging purposes
    if (debugMode)
    {
        galaxy1.showGalaxy();
        galaxy2.showGalaxy();
    }

    // Show initial data of stars
    std::cout << "Galaxy 1 has " << nrStars1 << " stars." << std::endl;
    std::cout << "Galaxy 2 has " << nrStars2 << " stars." << std::endl;
    double totalMass = 0.0f;
    for (const Star& star : galaxy1.getStars()) totalMass += star.getMass();
    for (const Star& star : galaxy2.getStars()) totalMass += star.getMass();
    std::cout << "Total Mass: " << totalMass << std::endl;
    std::cout << "The simulation runs " << iterations << " iterations." << std::endl;
    if (debugMode) std::cout << "DEBUG MODE ACTIVE!" << std::endl;

    // Run the simulation
    Simulation simulation(galaxy1, galaxy2, iterations);
    simulation.run();
}