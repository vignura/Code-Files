#include "sonobuoy.h"

/* function :: Sonobuoy()
    constructor with no parameters */
Sonobuoy::Sonobuoy(){
	
    this->pos.setCoord(0, 0, 0);
    this->TXFreq = 0;
    this->TXPower = 0;
}

/* function :: Sonobuoy()
    constructor with parameters */
Sonobuoy::Sonobuoy(Coordinate pos, double TXFreq, double TXPower){
	
    this->pos = pos;
    this->TXFreq = TXFreq;
    this->TXPower = TXPower;
}

/* function :: getPos()
    this function returns the current position of the 
    sonobuoy as a Coordinate object */
Coordinate Sonobuoy::getPos(){

    return this->pos;
}

/* function :: setPos()
    this function sets the current position of the
    sonobuoy to the new position given by 
    coordinate object passed */
void Sonobuoy::setPos(Coordinate pos){
   
    this->pos = pos;
}

/* function :: getFreq()
    this function returns the current TX frequency */

double Sonobuoy::getFreq(){
    
    return this->TXFreq;
}

/* function :: setFreq()
    this function sets the current TX frequency to 
    the passed value */
void Sonobuoy::setFerq(double Freq){

    this->TXFreq = Freq;
}

/* function :: getWavelen()
    this function returns the current operating 
    wave length of the Sonobuoy */
double Sonobuoy::getWavelen(){

    return ((double)c / this->TXFreq);
}

/* function :: getTXPower()
    this function returns the current TX power */
double Sonobuoy::getTXPower(){

    return this->TXPower;
}

/* function :: setTXPower()
    this function sets the current TX power to 
    the passed value */
void Sonobuoy::setTXPower(double TXPower){

     this->TXPower = TXPower;
}

/* function :: operator=()
    the overloaded assignment operator for
    Sonobuoy class */
void Sonobuoy::operator=(Sonobuoy Sbuoy){
    
    this->pos = Sbuoy.pos;
    this->TXFreq = Sbuoy.TXFreq;
    this->TXPower = Sbuoy.TXPower;
}

/* function :: ~Sonobuoy()
    destructor */
Sonobuoy::~Sonobuoy(){
    
    //deallocate any memory allocated 
}
