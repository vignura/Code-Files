#include "main.h"
using namespace std;

/* function :: main()
    The main function, that runs the simulation*/
int main(){
    // Initializing local variables
    double step; 
    FILE * fptr = NULL;
    long long int iteration;
    double x, y, z, heading, pitch, speed;
    double path[4], phase[4], phaseDiffFA, phaseDiffLR;
    double pathDiffLR, pathDiffFA;
    Coordinate sonobuoyLoc, helicopterLoc;
 
    cout << "Sonobuoy Phase Simulator" << endl;
 
    // getting Sonobuoy coordinate
    cout << "Enter sonobuoy coordinates (x y z): ";
    cin >> x >> y >> z;
    // initializing sonobuoy coordinate with user input
    sonobuoyLoc.setCoord(x,y,z);
    
    // getting the helicopter coordinate
    cout << "Enter helicopter coordinates (x y z): ";
    cin >> x >> y >> z;
    // initializing sonobuoy coordinate with user input
    helicopterLoc.setCoord(x,y,z);
    
    /* getting helicopter heading, pitch, speed, simulation minimum time step and 
    simulation iteration */
    cout << "Enter helicopter heading (0 to 360 deg): ";
    cin >> heading;
    cout << "Enter helicopter pitch (0 to 360 deg): ";
    cin >> pitch;
    cout << "Enter helicopter speed (m/s): ";
    cin >> speed;
    cout << "Enter the simulation minimum time step (sec): ";
    cin >> step;
    cout << "Enter number of iteration: ";
    cin >> iteration;
    
    /* Initializing a helicopter object with the user given input parameters 
    Note 1: the dFA and dLR ie the distance of separation between the antenna pairs is set to 1 meter 
    Note 2: the dFA is the distance of separation of Fore and Aft antenna pair and similarly,
            the dLR  is the distance of separation of Left and Right antenna pair*/ 
    Helicopter H1(helicopterLoc, 1, 1, pitch, heading, speed);
    
    /* Initializing a sonobuoy object with the user given input parameters
    Note: here sonobuoy Transmit frequency is set to 136 MHz */ 
    Sonobuoy S1(sonobuoyLoc, 136e6, 50);
    
    // creating a file for logging the data 
    fptr = fopen("PhaseCalc.csv", "w");
    
    // Writing the header
    fprintf(fptr, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", "Helicopter Position",\
                  "Fore Path (m)", "Aft Path (m)", "Left Path (m)", "Right Path (m)",\
                  "Phase Fore (deg)", "Phase Aft (deg)", "Phase Left (deg)", "Phase Right (deg)",\
                  "FA Path difference (m)", "FA Phase difference (deg)",\
                  "FA Path difference (m)", "LR Phase difference (deg)");
    
    /* Loop that runs for iteration number of times before exiting. This loop first calculates
        the path to all four antenna of the helicopter (Fore, Aft, Left, Right), then calculates 
        the phase difference between fore and aft antenna pair and left and right antenna pair.
        these calculations are done by moving the helicopter in for 'step' of time and re-evaluating
        the above calculations*/
    for(long long int i = 0; i < iteration; i++)
    {
        // calculating path from sonobuoy S1 to Helicopter H1's antennas 
        path[0] = findDis(S1.getPos(), H1.getForePos());
        path[1] = findDis(S1.getPos(), H1.getAftPos());
        path[2] = findDis(S1.getPos(), H1.getLeftPos());
        path[3] = findDis(S1.getPos(), H1.getRightPos());
        
        // calculating instantaneous phase at Helicopter H1's antennas 
        phase[0] = findPhase(path[0], S1.getWavelen());
        phase[1] = findPhase(path[1], S1.getWavelen());
        phase[2] = findPhase(path[2], S1.getWavelen());
        phase[3] = findPhase(path[3], S1.getWavelen());
        
        // calculating path difference and phase difference 
        pathDiffFA = (path[0] - path[1]);
        pathDiffLR = (path[2] - path[3]);
        phaseDiffFA = findPhaseDiff(pathDiffFA, phase[0], phase[1]);
        phaseDiffLR = findPhaseDiff(pathDiffLR, phase[2], phase[3]);
        
        // storing the above calculated values into csv file
        // printf("PhaseFore = %d\tPhaseAft = %d\n", (int)phase[0], (int)phase[1]);
        fprintf(fptr, "(%2.2f;%2.2f;%2.2f),%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f\n",\
                        (H1.getPos()).getx(), (H1.getPos()).gety(), (H1.getPos()).getz(),\
                        path[0], path[1], path[2], path[3],\
                        phase[0], phase[1], phase[2], phase[3],\
                        (pathDiffFA), phaseDiffFA, (pathDiffLR), phaseDiffLR);
        H1.flyFor(step); // time to fly for inbetween two samples
    }
    fclose(fptr);
    return 0;
}

/* function :: findDis()
    finds the distance between two points in 3D rectangular coordinates */
double findDis(Coordinate p1, Coordinate p2){
    
    return (sqrt( pow(p1.getx() - p2.getx(), 2) + pow( p1.gety() - p2.gety(), 2) + pow(p1.getz() - p2.getz(), 2) ) );
}

/* function :: findPhase()
    finds the instantaneous phase of a wave for the given path*/
double findPhase(double path, double Wavelen){
    
    long int mod;    
    //printf("path = %lf\t wave length = %lf\n", path, Wavelen);
    if(path > Wavelen){
        mod = path / Wavelen;
      return ( (path - (Wavelen * mod) ) / Wavelen * 360);
    }
    else{
        return ( (path / Wavelen) * 360 );
    }
}

/* function :: findPhaseDiff()
    finds the phase difference between two instantaneous phases 
    Note: the ph1 argument must be the phase of the antenna that is closest to the sonobuoy */
double findPhaseDiff(double pathDiff, double ph1, double ph2){

    // when pathDiff is negative, then the closest antenna's phase is ph1     
    if(pathDiff < 0){
    
        if(ph1 <= ph2){
            
            return abs(ph1 - ph2);
        }
        else{
            
            return ((360 -ph1) + ph2); 
        }
    }
    // when pathDiff is positive, then the closest antenna's phase is ph2
    else{
    
            if(ph2 <= ph1){
            
            return abs(ph2 - ph1);
        }
        else{
            
            return ((360 -ph2) + ph1); 
        }
    }
}

