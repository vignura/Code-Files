#include "phasor.h"

Phasor::Phasor(){

    this->amplitude = 0;
    this->phase = 0;
}

Phasor::Phasor(double amplitude, double phase){

    this->amplitude = amplitude;
    this->phase = phase;
}

void Phasor::toRect(double *x, double *y){

    *x = this->amplitude * cos(2 * M_PI *(this->phase / 180) );
    *y = this->amplitude * sin(2 * M_PI *(this->phase / 180) );
}

void Phasor::setRect(double x, double y){
    
    this->amplitude = sqrt( pow(x,2) + pow(y,2) );
    this->phase = (atan2(x,y) * 180) / M_PI;
    
    if(this->phase < 0){
        
        this->phase = 360 + this->phase;
    }
}


void Phasor::set(double amplitude, double phase){

    this->amplitude = amplitude;
    this->phase = phase;
}

void Phasor::setAmp(double amplitude){

    this->amplitude = amplitude;
}

void Phasor::setPhase(double phase){

    this->phase = phase;
}

double Phasor::getAmp(){

    return this->amplitude;
}

double Phasor::getPhase(){

    return this->phase;
}

void Phasor::operator=(Phasor ph){

    this->amplitude = ph.amplitude;
    this->phase = ph.phase;

}

Phasor::~Phasor(){
    
    // destroy
}

