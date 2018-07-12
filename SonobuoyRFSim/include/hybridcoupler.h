#ifndef _HYBRID_COUPLER_H_
#define _HYBRID_COUPLER_H_

#include "phasor.h"
#include "cstdio"

class HybridCoupler{

    double phase;
    double gain;
    Phasor A, B, C, D;
    
    void update();
    
public:
    
    HybridCoupler();
    HybridCoupler(double phase, double gain);
    
    void setInput(Phasor A, Phasor B);
    void getOutput(Phasor *C, Phasor *D);
    void operator=(HybridCoupler hc);
    
    ~HybridCoupler();

};

#endif // _HYBRID_COUPLER_H
