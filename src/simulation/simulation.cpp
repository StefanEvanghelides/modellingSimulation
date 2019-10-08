#include "simulation.h"
#include "../utils/constants.h"
#include <sstream>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>

/// Good option to keep in mind, might be useful later
#include <stdio.h>  /* defines FILENAME_MAX */
#ifdef _WIN32
    #include <direct.h>
    #include <process.h>
    #include <conio.h>
    #define GetCurrentDir _getcwd
#else
    #include <unistd.h>
    #define GetCurrentDir getcwd
#endif


void Simulation::run()
{
    std::cout << "Running the simulation!" <<std::endl;
    
    // Combine stars from galaxies
    std::vector<Star> stars1 = galaxy1.getStars();
    std::vector<Star> stars2 = galaxy2.getStars();
    copy (stars1.begin(), stars1.end(), back_inserter(this->stars));
    copy (stars2.begin(), stars2.end(), back_inserter(this->stars));

    // Ensure that the "data" folder exists
    std::ofstream dataDirectory;
    if (!directoryExists(DATA_DIRECTORY))
    {
        std::cout << "Directory doesn't exist! Attempting to create it..." <<std::endl;
        int errorDirCreated = mkdir(DATA_DIRECTORY);
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

    // show stars - DUMMY FUNCTION, DELETE THIS
    for (const Star& star : this->stars)
    {
        star.showStar();
    }

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
        file << "testing";
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

    if(stat( path, &info ) != 0)
        return false;
    else if(info.st_mode & S_IFDIR)
        return true;
    else
        return false;
}

std::string getBaseDirectory()
{
    char cCurrentPath[FILENAME_MAX];
    std::string baseDirectory;

    if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
    {
        std::cout << "Base directory could not be determined" << std::endl;
        return baseDirectory;
    } else
    {
        cCurrentPath[sizeof(cCurrentPath) - 1] = '\0';
        baseDirectory = cCurrentPath;
    }
    
    return baseDirectory;
}

// Gravitational Force formula
double gravitationalForce(const Star& s1, const Star& s2)
{
    const Coordinate c1 = s1.getCoord();
    const Coordinate c2 = s2.getCoord();
    double r = distance(c1, c2);
    double m1 = s1.getMass();
    double m2 = s2.getMass();

    return G * m1 * m2 / pow(r,2);
}

