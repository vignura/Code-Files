#include "signal.h"

Signal::Signal(){

    this->freq = 0;
    this->phase = 0;
}

Signal::Signal(double freq, double phase){

    this->freq = freq;
    this->phase = phase;
}

void Signal::operator=(Signal Sig){

    this->freq = Sig.freq;
    this->phase = Sig.phase;
}

void Signal::set(double freq, double phase){

    this->freq = freq;
    this->phase = phase;
}

void Signal::setFreq(double freq){

    this->freq = freq;
}

void Signal::setPhase(double phase){

    this->phase = phase;
}

double Signal::getFreq(){

    return this->freq;
}

double Signal::getPhase(){

    return this->phase;
}

double Signal::Sin(double time){

    //printf("time = %f\n", time);
    return sin( (2 * M_PIl * this->freq * time) + ((this->phase / 180) * M_PIl) );
}

double Signal::Cos(double time){

    return cos( (2 * M_PIl * this->freq * time) + ((this->phase / 180) * M_PIl) );
}
