#ifndef _CONSTANTS_H
#define _CONSTANTS_H

/**
 * This file contains the main constants used for
 * this application.
 */

#include <cmath>

// Newton's Gravity Constant and simulation acceleration
const double G = 6.6743 * pow(10, -11);
constexpr double SIM_ACC = 100000000;

// Minimum and maximum allowed mass for the stars.
// The values are in Solar Mass.
constexpr double MASS_MIN = 1.5 * SIM_ACC;
constexpr double MASS_MAX = 10 * SIM_ACC;

// Assume that the universe is a cube of coordinates
// (0,0,0) and (UNI_MAX, UNI_MAX, UNI_MAX).
// The second constant is the deviation.
constexpr double UNI_MAX = 1000000;
constexpr double UNI_MAX_DEV = UNI_MAX / 7;

// Minimum star speed and speed deviation
constexpr double DIR_MIN = -0.01;
constexpr double DIR_MIN_DEV = 0.02;

// Theta
constexpr double THETA = 0.5;

// Directory names
inline const char* DATA_DIRECTORY = "./data";

// Declare the debug mode, it is false by default
inline bool DEBUG_MODE = false;

// Set minimum allowed distance between the stars
// This should be dependent on the size of the universe
constexpr double STARS_MIN_DIST = UNI_MAX / 10000000;

#endif // _CONSTANTS_H