#include "antenna.h"

/* function :: Antenna() 
    Parameterless constructor */
Antenna::Antenna(){

    this->pos.setCoord(0, 0, 0);
    this->gain = 0;
}

/* function :: Antenna()
    Parameterized constructor */
Antenna::Antenna(Coordinate pos, double gain){

    this->pos = pos;
    this->gain = gain;
}

/* function :: getPos()
    Returns the position of the antenna as a Coordinate object */
Coordinate Antenna::getPos(){

    return this->pos;
}

/* function :: setPos()
    sets the position of the antenna to the passed Coordinate */
void Antenna::setPos(Coordinate pos){
    
    this->pos = pos;
}

/* function :: getGain()
    Returns antenna gain */
double Antenna::getGain(){
    
    return this->gain;
}
 
/* function :: setGain()
    sets the antenna gain to the passed value */
void Antenna::setGain(double gain){
    
    this->gain = gain;
}

/* function :: operator=()
    overloaded assignment operator for antenna class */
void Antenna::operator=(Antenna elem){
    
    this->pos = elem.pos;
    this->gain = elem.gain;
}

/* function :: ~Antenna()
    destructor */
Antenna::~Antenna(){

    //deallocate any memory allocated
}

