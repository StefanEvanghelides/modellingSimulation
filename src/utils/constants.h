#ifndef _CONSTANTS_H
#define _CONSTANTS_H

/**
 * This file contains the main constants used for
 * this application.
 */

#include <cmath>

// Newton's Gravity Constant
const double G = 6.6743 * pow(10,-11);

// Minimum and maximum allowed mass for the stars.
// The values are in Solar Mass.
const double MASS_MIN = 1.5;
const double MASS_MAX = 10;

// Assume that the universe is a cube of coordinates
// (0,0,0) and (UNI_MAX, UNI_MAX, UNI_MAX).
// The second constant is the deviation.
const double UNI_MAX = 1000;
const double UNI_MAX_DEV = 100;


#endif // _CONSTANTS_H