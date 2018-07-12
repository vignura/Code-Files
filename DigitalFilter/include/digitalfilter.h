#ifndef _DIGITAL_FILTER_H_
#define _DIGITAL_FILTER_H_

#include <deque>
#include <cstdio>

class DigitalFilter{

    double windowlen;
    std::deque<double> window;
    double output;
    
    void filter();
    
public:

    DigitalFilter();
    DigitalFilter(double windowlen);
    void operator=(DigitalFilter Filter);

    void setWindowLen(double windowlen);
    double getWindowLen();
    
    void Input(double sample);
    double Output();
    
    ~DigitalFilter();    
};

#endif // _DIGITAL_FILTER_H_
