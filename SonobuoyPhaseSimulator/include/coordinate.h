#ifndef _Coordinate_H_
#define _Coordinate_H_

class Coordinate{
// private members
    double x;
    double y;
    double z;

public:
// constructors
    Coordinate();
    Coordinate(double x, double y, double z);
// set functions
    void setCoord(double x, double y, double z);
    void setx(double x);
    void sety(double y);
    void setz(double z);
// get functions
    double getx();
    double gety();
    double getz();
// overloaded assignment operator
    void operator=(Coordinate p);
// destructor
    ~Coordinate();
};

#endif // _Coordinate_H_
