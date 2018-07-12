#ifndef _PHASOR_H_
#define _PHASOR_H_

#include <cmath>

class Phasor{
    
    double amplitude;
    double phase;
    
    void getRect(double *x, double *y);
    
public:
    
    Phasor();
    Phasor(double amplitude, double phase);
    
    void set(double amplitude, double phase);
    void setAmp(double amplitude);
    void setPhase(double phase);
    double getAmp();
    double getPhase();
    void toRect(double *x, double *y);
    void setRect(double x, double y);
    void operator=(Phasor ph);
    
    ~Phasor();
};
#endif // _PHASOR_H_
