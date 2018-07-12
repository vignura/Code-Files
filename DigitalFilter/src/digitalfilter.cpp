#include "digitalfilter.h"

DigitalFilter::DigitalFilter(){

    this->windowlen = 1;
    this->output = 0;
    this->window.assign(this->windowlen, 0);
}

DigitalFilter::DigitalFilter(double windowlen){

    this->windowlen = windowlen;
    this->output = 0;
    this->window.assign(this->windowlen, 0);
    // printf("created window of size %ld\n", this->window.size());
}

void DigitalFilter::operator=(DigitalFilter Filter){

    this->windowlen = Filter.windowlen;
    this->output = Filter.output;
    this->window = Filter.window;
}

void DigitalFilter::setWindowLen(double windowlen){
    
    this->windowlen = windowlen;
}

double DigitalFilter::getWindowLen(){
    
    return this->windowlen;
}

void DigitalFilter::Input(double sample){

    this->window.pop_front();
    this->window.push_back(sample);
}

double DigitalFilter::Output(){
    
    this->filter();
    return this->output;        
}

void DigitalFilter::filter(){

    unsigned long int i;
    
    for(i = 0; i < this->window.size(); i++)
    {
        this->output += this->window[i];
    }
    output /= this->window.size();
}

DigitalFilter::~DigitalFilter(){

    this->window.clear();
}
