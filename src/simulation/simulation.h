#ifndef _SIMULATION_H
#define _SIMULATION_H

#include "../models/galaxy.h"
#include "../octree/octree.h"
#include <string>

class Simulation
{
public:
    Simulation() = delete;
    Simulation(Galaxy galaxy1, Galaxy galaxy2, const size_t iterations)
        : galaxy1{galaxy1}, galaxy2{galaxy2}, iterations{iterations} {}
    ~Simulation() = default;

    void run();

private: // Private functions
    void update(size_t iteration);
    Octree generateOctree();
    void updateStars(Octree& tree);
    void exportIteration(size_t iteration);
    void plotIteration(size_t iteration);
    const std::string getFileName(size_t iteration, const std::string& extension);
    void writeToFile(const std::string& fileName);
    void removeOutOfBounds();
    void createOutputDir();

private: // Private members
    Galaxy galaxy1;
    Galaxy galaxy2;
    std::vector<Star> stars;
    size_t iterations;
    std::string outputDir;
};

// Forward declarations
bool directoryExists(const char *path);

#endif // _SIMULATION_H