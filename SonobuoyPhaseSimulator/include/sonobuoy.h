#ifndef _SONOBUOY_H
#define _SONOBUOY_H

#include "coordinate.h"
#define c 3e8

class Sonobuoy{
// private members
    Coordinate pos;
    double TXFreq;
    double TXPower;

public:
// constructors
    Sonobuoy();
    Sonobuoy(Coordinate pos, double TXFreq, double TXPower);
// functions to get and set Sonobuoy position    
    Coordinate getPos();
    void setPos(Coordinate pos);
// functions to get and set TX frequency and Wavelength   
    double getFreq();
    void setFerq(double Freq);
    double getWavelen();
// functions to get and set TX Wavelength
    double getTXPower();
    void setTXPower(double TXPower);
// overloaded assignment operator    
    void operator=(Sonobuoy Sbuoy);
// destructor    
    ~Sonobuoy();
};

#endif // _SONOBUOY_H
