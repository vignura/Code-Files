#include "main.h"

using namespace std;

int main(){
    
    FILE *fptr = NULL;
    HybridCoupler hc;
    Phasor a(10,0), b(10,0), c(10,0), d(10,0);
    
    printf("Sonobuoy RF Hybrid Copuler Simulator\n");
    
    fptr = fopen("RF_HybridCoupler_Sim.csv", "w");
    fprintf(fptr, "%s, ,%s, ,%s, ,%s\n", "PortA", "PortB", "PortC", "PortD");
    fprintf(fptr, "%s,%s,%s,%s,%s,%s,%s,%s\n",\
                     "Amplitude (V)", "Phase (deg)",\
                     "Amplitude (V)", "Phase (deg)",\
                     "Amplitude (V)", "Phase (deg)",\
                     "Amplitude (V)", "Phase (deg)");
    
    for(int i = 0; i < 10; i++)
    {
        a.setPhase((i * 10) + 40);
        // a.setPhase(10);
        b.setPhase(i * 10);
        
        hc.setInput(a,b);
        hc.getOutput(&c, &d);
        
        fprintf(fptr, "%f,%f,%f,%f,%f,%f,%f,%f\n",\
                        a.getAmp(), a.getPhase(),\
                        b.getAmp(), b.getPhase(),\
                        c.getAmp(), c.getPhase(),\
                        d.getAmp(), d.getPhase());

    }
     
    return 0;
}
