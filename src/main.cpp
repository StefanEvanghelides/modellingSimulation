#include <iostream>

// Global dummy counter;
size_t counter = 0;

typedef struct Galaxy
{
    size_t x; // dummy variable, just for now
} Galaxy;

void initializeGalaxy(Galaxy galaxy[], size_t nrStars1)
{
    for (size_t i = 0; i < nrStars1; i++)
    {
        galaxy[i].x = ++counter;
    }
}

void mergeGalaxies(Galaxy galaxy1[], size_t nrStars1, Galaxy galaxy2[], size_t nrStars2, Galaxy mGalaxy[])
{
    for (size_t i = 0; i < nrStars1; i++)
    {
        mGalaxy[i].x = galaxy1[i].x;
    }

    for (size_t i = 0; i < nrStars1; i++)
    {
        mGalaxy[nrStars1 + i].x = galaxy2[i].x;
    }
}

void updateStep(Galaxy galaxy[], size_t nrStars)
{
    for (size_t star = 0; star < nrStars; star++)
    {
        galaxy[star].x += 10;
    }
}

void printGalaxy(Galaxy galaxy[], size_t nrStars)
{
    std::cout << "Galaxy:" << std::endl;
    for (size_t i = 0; i < nrStars; i++)
    {
        std::cout << galaxy[i].x << " ";
    }
    std::cout << std::endl;
}

int main(int argc, char* argv[]){
    size_t iterations = 1000;
    size_t nrStars1 = 10;
    size_t nrStars2 = 10;

    Galaxy galaxy1[nrStars1];
    Galaxy galaxy2[nrStars2];
    Galaxy mGalaxy[nrStars1+nrStars2];

    initializeGalaxy(galaxy1, nrStars1);
    initializeGalaxy(galaxy2, nrStars1);
    mergeGalaxies(galaxy1, nrStars1, galaxy2, nrStars2, mGalaxy);

    for (size_t iter = 0; iter < iterations; iter++)
    {
        updateStep(mGalaxy, nrStars1+nrStars2);
    }

    printGalaxy(galaxy1, nrStars1);
    printGalaxy(galaxy2, nrStars2);
    printGalaxy(mGalaxy, nrStars1+nrStars2);
}
