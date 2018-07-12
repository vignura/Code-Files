#ifndef _SIGNAL_H_
#define _SIGNAL_H_

#include <cmath>
#include <cstdio>
class Signal{

    double freq;
    double phase;
    
public:
    Signal();
    Signal(double freq, double phase);
    void operator=(Signal Sig);

    void set(double freq, double phase);
    void setFreq(double freq);
    void setPhase(double phase);

    double getFreq();
    double getPhase();

    double Sin(double time);
    double Cos(double time);
};
#endif  // _SIGNAL_H_
