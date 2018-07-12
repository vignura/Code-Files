#ifndef _HELICOPTER_H_
#define _HELICOPTER_H_

#include <cstring>
#include <cmath>
#include <cstdio>
#include "antenna.h" 
#include "coordinate.h"

#define FORE_HEADING_OFFSET     0
#define AFT_HEADING_OFFSET      180
#define LEFT_HEADING_OFFSET     90
#define RIGHT_HEADING_OFFSET    270
#define PI 3.141592654
// #define DEBUG

class Helicopter{
// private members 
    Coordinate pos;
    Antenna fore;
    Antenna aft;
    Antenna left;
    Antenna right;
    double dFA;
    double dLR;
    double pitch;
    double heading;
    double speed;
// private member functions  
    void updateAntennaPos();
    void setAntennaPos(const char *antenna);
    
public:
// constructors
    Helicopter();
    Helicopter(Coordinate pos, double dFA, double dLR);
    Helicopter(Coordinate pos, double dFA, double dLR, double pitch, double heading);
    Helicopter(Coordinate pos, double dFA, double dLR, double pitch, double heading, double speed);
// overloaded assignment operator
    void operator=(Helicopter H1);
// functions to move the helicopter to that point
    void moveto(double x, double y, double z);
    void moveXto(double x);
    void moveYto(double y);
    void moveZto(double z);
// functions to move the helicopter from the current point by given amount
    void moveby(double x, double y, double z);
    void moveXby(double x);
    void moveYby(double y);
    void moveZby(double z);
// flies the helicopter for given amount of time
    void flyFor(double time);
// functions to set, get and change heading of helicopter
    void setHeading(double heading);
    void changeHeading(double inc);
    double getHeading();
// functions to set, get and change pitch of helicopter
    void setPitch(double pitch);
    void changePitch(double inc);
    double getPitch();
// functions to set, get and change speed of helicopter
    void setSpeed(double speed);
    void changeSpeed(double inc);
    double getSpeed();
// functions to set and get fore-aft antenna separation distance
    void setdFA(double dFA);
    double getdFA();
// functions to set and get left-right antenna separation distance
    void setdLR(double dFA);
    double getdLR();
// functions to get helicopter and antenna coordinates
    Coordinate getPos();
    Coordinate getForePos();
    Coordinate getAftPos();
    Coordinate getLeftPos();
    Coordinate getRightPos();
// destructor
    ~Helicopter();
    
};

#endif //_HELICOPTER_H_
