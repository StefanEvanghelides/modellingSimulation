#include "models/simulation.h"

int main(int argc, char** argv)
{
    // User input - galaxy center
    const Coordinate galaxyCenter1 {200, 500, 500};
    const Coordinate galaxyCenter2 {800, 500, 500};

    // User input - number of stars
    const size_t nrStars1 = 10;
    const size_t nrStars2 = 10;

    // User input - number of iterations
    const size_t iterations = 1000;

    Galaxy galaxy1 {galaxyCenter1, nrStars1};
    Galaxy galaxy2 {galaxyCenter2, nrStars2};

    galaxy1.showGalaxy();
    galaxy2.showGalaxy();

    // Run the simulation
    Simulation simulation(galaxy1, galaxy2, iterations);
    simulation.run();
}