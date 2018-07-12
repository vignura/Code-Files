#include "main.h"

using namespace std;

int main(){

    double startfreq;
    double stopfreq;
    double freqstep;
    double windowlen;
    double stoptime;
    double timestep;
    double samplingfreq;
    double simfreq = 0;
    double simtime = 0;
    FILE *fptr;
    
    cout << "Digital Filter" << endl;
    cout << "Enter Start Frequency (Hz): ";
    cin >> startfreq;
    cout << "Enter Stop Frequency (Hz): ";
    cin >> stopfreq;
    cout << "Enter Frequency sampling interval (Hz): ";
    cin >> freqstep; 
    cout << "Enter window length: ";
    cin >> windowlen;
    cout << "Enter sampling frequency (Hz): ";
    cin >> samplingfreq;
    cout << "Enter simulation stop time (sec):";
    cin >> stoptime;
    
    timestep = 1 / samplingfreq;
    simfreq = startfreq;
    Signal sig;
    vector <DigitalFilter> F;
    
    fptr = fopen("FilterResponse.csv", "w");
    
    for(long i = 0; simfreq <= stopfreq; i++)
    {
        fprintf(fptr, "%f Hz,", simfreq);
        simfreq += freqstep;
        DigitalFilter F1(windowlen);
        F.push_back(F1);
    }
    
    fprintf(fptr, "filterResponse\n");    

    //for(long j = 0; j < 250; j++)
    for(long j = 0; simtime <= stoptime; j++)
    {      
        simfreq = startfreq;
        //cout << "j = " << j << endl;
        //for(long i = 0; i < 5; i++)            
        for(long i = 0; simfreq <= stopfreq; i++)
        {
            //cout << "i = " << i << endl;
            sig.set(simfreq, 0);
            F[i].Input(sig.Sin(simtime));    
            fprintf(fptr, "%f,", F[i].Output());
            simfreq += freqstep;  
            //printf("simfreq = %f\n", simfreq);             
        }
        fprintf(fptr, "\n");
        
        simtime += timestep;
    }
    
    fclose(fptr);
    return 0;
}
