#include "simulation.h"
#include "../utils/constants.h"
#include <sstream>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <algorithm>
#include <chrono>

typedef std::chrono::high_resolution_clock Clock;

void Simulation::run()
{
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
    else if (DEBUG_MODE)
    {
        std::cout << "Directory already exists! Nothing needs to be done" << std::endl;
    }

    // Run the simulation.
    // Also start a timer
    auto startTime = Clock::now();
    for (size_t iter = 0; iter < iterations; iter++)
    {
        if (DEBUG_MODE)
        {
            std::cout << std::endl << " ----- Iteration " << iter << " ----- " << std::endl;
        }
        if (stars.size() < 2)
        {
            std::cout << "There are less than 2 stars in the Universe!" << std::endl
                      << "Simulation stopped!" << std::endl;
            break;
        }
        update(iter);
    }
    auto endTime = Clock::now();
    std::chrono::duration<double> duration = endTime - startTime;
    std::cout << "Total time: "
              << std::chrono::duration_cast<std::chrono::seconds>(duration).count()
              << " seconds!" << std::endl;
    std::cout << "Number of stars left: " << stars.size() << std::endl;;
}

void Simulation::update(size_t iteration)
{
    // Export the current state of the stars to a file.
    // The export is executed first in order to show the initial state of the galaxies.
    exportIteration(iteration);

    // Generate the octree.
    Octree tree = generateOctree();

    // Show each tree only in second debug mode
//    if (DEBUG_MODE == 2) tree.showTree();

    // Calculate forces and update stars.
    updateStars(tree);
}

// Generate the octree based on the current state of the stars.
Octree Simulation::generateOctree()
{
    Octree tree { {0}, { UNI_MAX } };

    for (const Star& star : stars)
    {
        tree.insert(star);
    }
    return tree;
}

// Save the new state of the stars.
void Simulation::updateStars(Octree& tree)
{
    removeOutOfBounds();

    const size_t nrStars = stars.size();

    #pragma omp parallel for
    for (size_t i = 0; i < nrStars; ++i)
    {
        Coordinate force = tree.calculateForce(stars[i]);
        stars[i].setDir(stars[i].getDir() + force);
        stars[i].setCoord(stars[i].getCoord() + stars[i].getDir());
    }
}

void Simulation::removeOutOfBounds()
{
    size_t nStars = stars.size();
    stars.erase(std::remove_if(stars.begin(), stars.end(),
        [] (const Star& star) {
            Coordinate c = star.getCoord();
            return (c.x < 0 || c.y < 0 || c.z < 0 ||
                    c.x > UNI_MAX || c.y > UNI_MAX || c.z > UNI_MAX);
        }
    ), stars.end());
    if (DEBUG_MODE && nStars != stars.size())
        std::cout << nStars - stars.size() << " stars went out of bounds.\n"
                  << "Remaining: " << stars.size() << std::endl;
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

    size_t pad = 1;
    size_t i = iterations;
    while (i > 0)
    {
        pad *= 10;
        i /= 10;
    }

    i = iteration;
    if (i == 0) i++;
    std::string padding = "";
    while (i < pad)
    {
        padding.append("0");
        i *= 10;
    }

    std::stringstream ss;
    ss  << nrStars1 << "-by-" << nrStars2
        << "_iterations=" << this->iterations
        << "_theta=" << THETA
        << "_step=" << padding << iteration
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
             << "# Galaxy  X          Y          Z          DX      DY      DZ" << std::endl;

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