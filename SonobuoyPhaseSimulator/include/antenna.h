#ifndef _ANTENNA_H_
#define _ANTENNA_H_

#include "coordinate.h"

class Antenna{
// private members    
    Coordinate pos;
    double gain;

public:
// constructors
    Antenna();
    Antenna(Coordinate pos, double gain);
// functions set and get antenna position
    Coordinate getPos();
    void setPos(Coordinate pos);
// functions set and get antenna gain
    double getGain();
    void setGain(double gain);
// overloaded assignment operator    
    void operator=(Antenna elem);
// destructor    
    ~Antenna();
};

#endif //_ANTENNA_H_
