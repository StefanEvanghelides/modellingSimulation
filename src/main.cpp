#include "simulation/simulation.h"
#include "octree/octree.h"
#include "utils/constants.h"
#include "utils/argparse.h"
#include <iostream>
#include <cstring>

int main(int argc, char** argv)
{
    // Default galaxy centers
    const Coordinate galaxyCenter1 {0.2 * UNI_MAX, UNI_MAX/2, UNI_MAX/2};
    const Coordinate galaxyCenter2 {0.8 * UNI_MAX, UNI_MAX/2, UNI_MAX/2};


    argparse::ArgumentParser parser("run");
    parser.add_argument("-d", "--debug")
      .help("increase output verbosity")
      .default_value(0)
      .implicit_value(1);
    parser.add_argument("-i", "--iterations")
      .help("Number of iterations")
      .default_value(500)
      .action([](const std::string& value) { return std::stoi(value); });
    parser.add_argument("-s1", "--stars1")
      .help("Number of stars in the first galaxy")
      .default_value(1000)
      .action([](const std::string& value) { return std::stoi(value); });
    parser.add_argument("-s2", "--stars2")
      .help("Number of stars in the second galaxy")
      .default_value(1000)
      .action([](const std::string& value) { return std::stoi(value); });
    parser.add_argument("-t", "--theta")
      .help("Theta value, based on the Barnes-Hut algorithm")
      .default_value(0.5)
      .action([](const std::string& value) { return std::stod(value); });
    parser.add_argument("-p", "--plot")
      .help("Automatically plot the stars")
      .default_value(false)
      .implicit_value(true);

    try {
      parser.parse_args(argc, argv);
    }
    catch (const std::runtime_error& err) {
      std::cout << err.what() << std::endl;
      std::cout << parser;
      exit(0);
    }

    size_t nrStars1 = parser.get<int>("-s1");
    size_t nrStars2 = parser.get<int>("-s2");
    size_t iterations = parser.get<int>("-i");
    THETA = parser.get<double>("-t");
    DEBUG_MODE = parser.get<int>("-d");
    PLOT = parser.get<bool>("-p");

    // Increase simulation acceleration for low number of stars
    SIM_ACC = SIM_ACC / (nrStars1 + nrStars2);

    //
    // --------------------------------------------------------
    // Generate the galaxies
    Galaxy galaxy1 {galaxyCenter1, nrStars1};
    Galaxy galaxy2 {galaxyCenter2, nrStars2};

    // Show galaxies for debbuging purposes
    if (DEBUG_MODE == 2)
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
    std::cout << "Theta: " << THETA << std::endl;
    if (DEBUG_MODE) std::cout << "DEBUG MODE ACTIVE!" << std::endl;

    // Run the simulation
    Simulation simulation(galaxy1, galaxy2, iterations);
    simulation.run();
}