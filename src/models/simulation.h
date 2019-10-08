#ifndef _SIMULATION_H
#define _SIMULATION_H

#include "galaxy.h"

class Simulation
{
public:
    Simulation() = delete;
    Simulation(Galaxy galaxy1, Galaxy galaxy2, const size_t iterations)
        : galaxy1{galaxy1}, galaxy2{galaxy2}, iterations{iterations} {}
    ~Simulation() = default;

    void run();
private:
    Galaxy galaxy1;
    Galaxy galaxy2;
    std::vector<Star> stars;
    size_t iterations;
};

// Forward declarations
Galaxy mergeGalaxies(Galaxy galaxy1, Galaxy galaxy2);


#endif // _SIMULATION_H