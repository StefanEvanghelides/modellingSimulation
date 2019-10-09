#include "simulation.h"
#include "../utils/constants.h"
#include "../octree/octree.h"
#include <sstream>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>

void Simulation::run()
{
    std::cout << "Running the simulation!" << std::endl;
    
    // Combine stars from galaxies
    std::vector<Star> stars1 = galaxy1.getStars();
    std::vector<Star> stars2 = galaxy2.getStars();
    copy (stars1.begin(), stars1.end(), back_inserter(this->stars));
    copy (stars2.begin(), stars2.end(), back_inserter(this->stars));

    // Ensure that the "data" folder exists
    std::ofstream dataDirectory;
    if (!directoryExists(DATA_DIRECTORY))
    {
        std::cout << "Directory doesn't exist! Attempting to create it..." << std::endl;
        #ifdef _WIN32
            int errorDirCreated = mkdir(DATA_DIRECTORY);
        #else
            int errorDirCreated = mkdir(DATA_DIRECTORY, 0777);
        #endif
        if (errorDirCreated)
        {
            std::cout << "Directory could not be created!" << std::endl;
            exit(0);
        }
        else
        {
            std::cout << "Directory created successful!" << std::endl;
        }
    }

    // Run the simulation
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

// Writes the iteration status to the file in "data" folder.
// Note: It is assumed that the folder "data" already exists
void Simulation::exportIteration(size_t iteration)
{
    // Generate the name of the file
    const std::string& fileName = getFileName(iteration);

    // Export to file
    writeToFile(fileName);
}

const std::string Simulation::getFileName(size_t iteration)
{
    const size_t nrStars1 = galaxy1.getNrStars();
    const size_t nrStars2 = galaxy2.getNrStars();

    std::stringstream ss;
    ss  << nrStars1 << "-by-" << nrStars2
        << "_iterations=" << this->iterations
        << "_step=" << iteration
        << ".dat"; // extension

    return ss.str();
}

void Simulation::writeToFile(const std::string& fileName)
{
    std::string path = std::string(DATA_DIRECTORY) + "/" + fileName;
    std::ofstream file {path};
    if (file.is_open())
    {
        // Write file header commentary
        // Note: This file is expected to be run in python, so use python comment syntax
        file << "# This file was created for the Modelling and Simulation course, RUG (September-November 2019)." << std::endl
             << "#" << std::endl
             << "# Project: Simulate colliding galaxies, using Barnes-Hut algorithm." << std::endl
             << "#" << std::endl
             << "# Students:" << std::endl
             << "#     Stefan Evanghelides (s2895323)" << std::endl
             << "#     Hidde Folkertsma (s2759799)" << std::endl
             << "#" << std::endl
             << "#     X         Y         Z         DX        DY        DZ" << std::endl;

        // Write the stars
        for (const Star& star : stars)
        {
            file << star.exportString();
        }

        file.close();
    }
    else
    {
        std::cout << "File " << fileName << " could not be opened!";
    }
}

// Portable C-like function with no dependencies
bool directoryExists(const char *path)
{
    struct stat info;

    if (stat(path, &info) != 0)
        return false;
    else if (info.st_mode & S_IFDIR)
        return true;
    else
        return false;
}

// Gravitational Force formula
double gravitationalForce(const Star& s1, const Star& s2)
{
    const Coordinate c1 = s1.getCoord();
    const Coordinate c2 = s2.getCoord();
    double r = distance(c1, c2);
    double m1 = s1.getMass();
    double m2 = s2.getMass();

    return G * m1 * m2 / pow(r, 2);
}

