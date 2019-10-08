#ifndef _SIMULATION_H
#define _SIMULATION_H

#include "../models/galaxy.h"

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
    void exportIteration(size_t iteration);
    std::string getFileName(size_t iteration);

private: // Private members
    Galaxy galaxy1;
    Galaxy galaxy2;
    std::vector<Star> stars;
    size_t iterations;
};

#endif // _SIMULATION_H