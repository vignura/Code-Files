#ifndef SONOBUOY_PHASE_SIM_MAIN_H_
#define SONOBUOY_PHASE_SIM_MAIN_H_

// list of includes
#include <iostream>
#include <cstdio>
#include <fstream>

#include "helicopter.h"
#include "sonobuoy.h" 

// function declarations
double findDis(Coordinate p1, Coordinate p2);
double findPhase(double path, double Wavelen);
double findPhaseDiff(double pathDiff, double ph1, double ph2);

#endif // SONOBUOY_PHASE_SIM_MAIN_H_
