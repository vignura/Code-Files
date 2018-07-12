#include "helicopter.h"

/* function :: Helicopter()
    parameter less constructor */
Helicopter::Helicopter(){
    
    this->pos.setCoord(0, 0, 0);
    this->dFA = 2;
    this->dLR = 2;
    this->pitch = 90;           // pitch 90 deg = parallel to surface
    this->heading = 0;          // heading 0 deg = east
    this->speed = 10;           // 10 m/s initial speed
    this->updateAntennaPos();
}

/* function :: Helicopter()
    parameterized constructor with preset values for
    pitch, heading and speed */
Helicopter::Helicopter(Coordinate pos, double dFA, double dLR){
    
    this->pos = pos;
    this->dFA = dFA;
    this->dLR = dLR;
    this->pitch = 90;           // pitch 90 deg = parallel to surface
    this->heading = 0;          // heading 0 deg = east
    this->speed = 10;           // 10 m/s initial speed
    this->updateAntennaPos();
}

/* function :: Helicopter()
    parameterized constructor with preset values for speed */
Helicopter::Helicopter(Coordinate pos, double dFA, double dLR, double pitch, double heading){
    
    this->pos = pos;
    this->dFA = dFA;
    this->dLR = dLR;
    this->pitch = pitch;
    this->heading = heading;
    this->speed = 10;           // 10 m/s initial speed
    this->updateAntennaPos();
}

/* function :: Helicopter()
    parameterized constructor */
Helicopter::Helicopter(Coordinate pos, double dFA, double dLR, double pitch, double heading, double speed){
    
    this->pos = pos;
    this->dFA = dFA;
    this->dLR = dLR;
    this->pitch = pitch;
    this->heading = heading;
    this->speed = speed;
    this->updateAntennaPos();
}

/* function :: operator=()
    overloaded assignment operator for Helicopter class */
void Helicopter::operator=(Helicopter H1){
    
    this->pos = H1.pos;
    this->dFA = H1.dFA;
    this->dLR = H1.dLR;
    this->pitch = H1.pitch;
    this->heading = H1.heading;
    this->updateAntennaPos();
}

/* function :: updateAntennaPos()
    function to update position of fore, aft, left and right
    antennas with respect to helicopter's position */
void Helicopter::updateAntennaPos(){
    
    this->setAntennaPos("fore");
    this->setAntennaPos("aft");
    this->setAntennaPos("left");
    this->setAntennaPos("right");
}

/* function :: setAntennaPos()
    this function claculates the position of the given antenna
    based on the helicopter's position. the coordinates are calculated
    by finding the position of antenna in spherical coordinate and then converting
    it back to rectangular coordinates */
void Helicopter::setAntennaPos(const char *antenna){

    double radius, heading;
    unsigned char antennaNo;
    Coordinate antennaPos;
    
    if(!strcmp("fore", antenna))
    {
        heading = this->heading + FORE_HEADING_OFFSET;
        radius = this->dFA / 2;
        antennaNo = 1;
    }
    else if(!strcmp("aft", antenna))
    {
        heading = this->heading + AFT_HEADING_OFFSET;
        radius = this->dFA / 2;
        antennaNo = 2;
    }
    else if(!strcmp("left", antenna))
    {
        heading = this->heading + LEFT_HEADING_OFFSET;
        radius = this->dLR / 2;
        antennaNo = 3;
    }
    else if(!strcmp("right", antenna))
    {
        heading = this->heading + RIGHT_HEADING_OFFSET;
        radius = this->dLR / 2;
        antennaNo = 4;
    }
    else
    {
        // cover invalid input here
    }

#ifdef DEBUG
    printf("Radius: %f\t heading: %f\t antennaNo: %d\n", radius, heading, antennaNo);
#endif    

    antennaPos.setx( ( (radius * sin(M_PIl * (pitch / 180.0f) )) * cos(M_PIl * (heading / 180.0f) )) + this->pos.getx() );
    antennaPos.sety( ( (radius * sin(M_PIl * (pitch / 180.0f) )) * sin(M_PIl * (heading / 180.0f) )) + this->pos.gety() );
    antennaPos.setz( (radius * cos(M_PIl * (pitch / 180.0f) )) + this->pos.getz() );
    
    switch(antennaNo){
        
        case 1: this->fore.setPos(antennaPos); break;
        case 2: this->aft.setPos(antennaPos); break;
        case 3: this->left.setPos(antennaPos); break;
        case 4: this->right.setPos(antennaPos); break;
    }
#ifdef DEBUG
    printf("%s position [%f, %f, %f]\n", antenna, antennaPos.getx(), antennaPos.gety(), antennaPos.getz());
#endif
}

/* function :: moveto()
    moves the helicopter to the given x,y,z coordinate */
void Helicopter::moveto(double x, double y, double z){

    this->pos.setCoord(x, y, z);
    this->updateAntennaPos();
}

/* function :: moveXto()
    moves the x coordinates to the given x value */
void Helicopter::moveXto(double x){

    this->pos.setx(x);
    this->updateAntennaPos();
}

/* function :: moveYto()
    moves the y coordinates to the given y value */
void Helicopter::moveYto(double y){

    this->pos.sety(y);
    this->updateAntennaPos();
}

/* function :: moveZto()
    moves the z coordinates to the given z value */
void Helicopter::moveZto(double z){

    this->pos.setz(z);
    this->updateAntennaPos();
}

/* function :: moveby()
    increments the x, y and z coordinates by the given x, y and z value */
void Helicopter::moveby(double x, double y, double z){

    this->pos.setCoord( (x + this->pos.getx() ), (y + this->pos.gety() ), (z + this->pos.getz() ) );
    this->updateAntennaPos();
    // printf("\nHelipos (%f,%f,%f) \t(x,y,z) = (%f,%f,%f)", this->pos.getx(), this->pos.gety(), this->pos.getz(), x, y, z);
}

/* function :: moveXby()
    increments the x coordinates by the given x value */
void Helicopter::moveXby(double x){

    this->pos.setx(x + this->pos.getx());
    this->updateAntennaPos();
}

/* function :: moveYby()
    increments the y coordinates by the given y value */
void Helicopter::moveYby(double y){

    this->pos.sety(y + this->pos.gety());
    this->updateAntennaPos();
}

/* function :: moveZby()
    increments the z coordinates by the given z value */
void Helicopter::moveZby(double z){

    this->pos.setz(z + this->pos.getz());
    this->updateAntennaPos();
}

/* function :: flyFor()
    this function simulates flying helicopter. it moves the 
    helicopter in the "direction" given by the heading and pitch of 
    the helicopter and the "distance traveled" by the helicopter
    is calculated using the speed and 'time' argument */
void Helicopter::flyFor(double time){
    
    double distance = this->speed * time;
    this->moveby( (distance * sin(M_PIl * (this->pitch / 180.0f)) * cos(M_PIl * (this->heading / 180.0f)) ), 
    (distance * sin(M_PIl * (this->pitch / 180.0f)) * sin(M_PIl * (this->heading / 180.0f)) ), 
    (distance * cos(M_PIl * (this->pitch / 180.0f))) );
}

/* function :: setHeading()
    this function sets the current heading to value passed */
void Helicopter::setHeading(double heading){

    this->heading = heading;
}

/* function :: changeHeading()
    this function changes heading of the helicopter by the
    passed(inc) amount */
void Helicopter::changeHeading(double inc){

    this->heading += inc;
}

/* function :: getHeading()
    this function returns the current heading of the 
    helicopter */
double Helicopter::getHeading(){

    return this->heading;
}

/* function :: setPitch()
    this function the sets the current pitch to the 
    passed(inc) value */
void Helicopter::setPitch(double pitch){

    this->pitch = pitch;
}

/* function :: changePitch()
    this function changes the pitch of the helicopter
    by the amount given by 'inc' */
void Helicopter::changePitch(double inc){

    this->pitch += inc;
}

/* function :: getPitch()
    this function returns the current pitch of the 
    helicopter */
double Helicopter::getPitch(){

    return this->pitch;
}

/* function :: setSpeed()
    this function sets the helicopter's current speed
    to the passed value(speed) */
void Helicopter::setSpeed(double speed){

    this->speed = speed;
}

/* function :: changeSpeed()
    this function changes the current speed by the 
    value passed(inc) */
void Helicopter::changeSpeed(double inc){

    this->speed += inc;
}

/* function :: getSpeed()
    this function returns the helicopter's current speed */
double Helicopter::getSpeed(){

    return this->speed;
}

/* function :: setdFA()
    this function sets the current dFA to the passed value
    Note: dFA is the distance of separation between fore and 
    aft antenna pairs */
void Helicopter::setdFA(double dFA){

    this->dFA  = dFA;
}

/* function :: getdFA()
    this function returns the current dFA */
double Helicopter::getdFA(){

    return this->dFA;
}

/* function :: setdLR()
    this function sets the current dLR to the passed value
    Note: dFA is the distance of separation between left and 
    right antenna pairs */
void Helicopter::setdLR(double dFA){

    this->dFA  = dLR;
}

/* function :: getdLR()
    this function returns the current dLR */
double Helicopter::getdLR(){

    return this->dLR;
}

/* function :: getPos()
    this function return the helicopter's current position
    and the return type is Coordinate */
Coordinate Helicopter::getPos(){

    return this->pos;
}

/* function :: getForePos()
    this function returns the current position of 
    fore antenna as a Coordinate object */
Coordinate Helicopter::getForePos(){

    return this->fore.getPos();
}

/* function :: getAftPos()
    this function returns the current position of 
    aft antenna as a Coordinate object */
Coordinate Helicopter::getAftPos(){

    return this->aft.getPos();
}

/* function :: getLeftPos()
    this function returns the current position of 
    left antenna as a Coordinate object */
Coordinate Helicopter::getLeftPos(){

    return this->left.getPos();
}

/* function :: getRightPos()
    this function returns the current position of 
    right antenna as a Coordinate object */
Coordinate Helicopter::getRightPos(){

    return this->right.getPos();
}

/* function :: ~Helicopter() 
    destructor */
Helicopter::~Helicopter(){

    //deallocate any memory allocated
}

