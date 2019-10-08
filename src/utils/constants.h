#ifndef _CONSTANTS_H
#define _CONSTANTS_Hs

/**
 * This file contains the main constants used for
 * this application.
 */

#include <cmath>

// Newton's Gravity Constant
const double G = 6.6743 * pow(10,-11);

// Minimum and maximum allowed mass for the stars.
// The values are in Solar Mass.
constexpr double MASS_MIN = 1.5;
constexpr double MASS_MAX = 10;

// Assume that the universe is a cube of coordinates
// (0,0,0) and (UNI_MAX, UNI_MAX, UNI_MAX).
// The second constant is the deviation.
constexpr double UNI_MAX = 1000;
constexpr double UNI_MAX_DEV = 100;

// Minimum star speed and speed deviation
constexpr double DIR_MIN = -0.1;
constexpr double DIR_MIN_DEV = 0.2;

// Directory names
inline const char* DATA_DIRECTORY = "./data";

#endif // _CONSTANTS_H