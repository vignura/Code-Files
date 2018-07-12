#include "coordinate.h"

/* function :: Coordinate() 
    Parameterless constructor */
Coordinate::Coordinate(){
 
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

/* function :: Coordinate()
    Parameterised constructor */
Coordinate::Coordinate(double x, double y, double z){
 
    this->x = x;
    this->y = y;
    this->z = z;
}

/* function :: setCoord()
    This function sets the values of x, y, z members to the passed parameters*/
void Coordinate::setCoord(double x, double y, double z){
 
    this->x = x;
    this->y = y;
    this->z = z;
}

/* function :: setx()
    This function sets the value of member x to passed value */
void Coordinate::setx(double x){
    this->x = x;
}

/* function :: sety()
    This function sets the value of member y to passed value */
void Coordinate::sety(double y){
    this->y = y;
}

/* function :: setz()
This function sets the value of member z to passed value */
void Coordinate::setz(double z){
    this->z = z;
}

/* function :: operator=()
    Assignment operator overloaded for Coordinate class
    It alows the use of '=' operator with coordinate objects */
void Coordinate::operator=(Coordinate p){

    this->x = p.getx();
    this->y = p.gety();
    this->z = p.getz();
}

/* function :: getx()
    This function return the x coordinate */
double Coordinate::getx(){

    return this->x;
}

/* function :: gety()
    This function return the y coordinate */
double Coordinate::gety(){

    return this->y;
}

/* function :: getz()
    This function return the z coordinate */
double Coordinate::getz(){

    return this->z;
}

/* function :: ~Coordinate()
    Destructor for class Coordinate*/
Coordinate::~Coordinate(){
    
    //de allocate any memory allocated 
}
