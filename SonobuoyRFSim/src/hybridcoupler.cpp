#include "hybridcoupler.h"

HybridCoupler::HybridCoupler(){

    this->phase = 90;
    this->gain = pow(2, -0.5);  
    this->A.set(0, 0);
    this->B.set(0, 0);
    this->C.set(0, 0);
    this->D.set(0, 0);
}

HybridCoupler::HybridCoupler(double phase, double gain){

    this->phase = phase;
    this->gain = gain; 
    this->A.set(0, 0);
    this->B.set(0, 0);
    this->C.set(0, 0);
    this->D.set(0, 0);
}

void HybridCoupler::setInput(Phasor A, Phasor B){

    this->A = A;
    this->B = B;
    this->update();
}

void HybridCoupler::getOutput(Phasor *C, Phasor *D){

    *C = this->C;
    *D = this->D;
}

void HybridCoupler::update(){

    double cx, cy, dx, dy;
    Phasor a, b, c, d;
    
    a = this->A;
    printf("PortA: phase: %f deg\n", a.getPhase());
    a.setPhase( a.getPhase() - 90);
    printf("PortC: phaseA@C: %f deg\n", a.getPhase());
    b = this->B;
    printf("PortB: phase: %f deg\n", b.getPhase());
    b.setPhase( b.getPhase() - 180);
    printf("PortC: phaseB@C: %f deg\n", b.getPhase());
    
    a.toRect(&cx, &cy);
    b.toRect(&dx, &dy);
    
    printf("PortC: Voltage A@C (x, y): (%f, %f)\n", cx, cy);
    printf("PortC: Voltage B@C (x, y): (%f, %f)\n", dx, dy);
    
    cx = this->gain * (cx + dx);
    cy = this->gain * (cy + dy);
    printf("gain : %f\n", this->gain);
    printf("PortC: Voltage(x, y): (%f, %f)\n\n", cx, cy);
    
    c.setRect(cx, cy);
    this->C = c;
    
    
    a = this->A;
    a.setPhase( a.getPhase() - 180);
    b = this->B;
    b.setPhase( b.getPhase() - 90);
    
    a.toRect(&cx, &cy);
    b.toRect(&dx, &dy);
    
    dx = this->gain * (cx + dx);
    dy = this->gain * (cy + dy);
    
    d.setRect(dx, dy);
    this->D = d;
}

void HybridCoupler::operator=(HybridCoupler hc)
{
    this->phase = hc.phase;
    this->gain = hc.gain;
    this->A = hc.A;
    this->B = hc.B;
    this->C = hc.C;
    this->D = hc.D; 
}

HybridCoupler::~HybridCoupler(){
    
    //destroy
}
