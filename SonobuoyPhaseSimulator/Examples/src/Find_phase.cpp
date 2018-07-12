#include  <iostream>
using namespace std;

double findPhase(double path, double Wavelen){
    
    long int mod;    
        
    if(path > Wavelen){
        mod = path / Wavelen;
      return ( (path - (Wavelen * mod) ) / Wavelen * 360);
    }
    else{
        return ( (path / Wavelen) * 360 );
    }
}

int main(){
    double path, wavelen;
    do{
        cout << "Enter path and wavelength in meters: ";
        cin >> path >> wavelen;
        cout << "phase = " << findPhase(path, wavelen) <<" deg" << endl;
    }while(wavelen != 0); 
    return 0;
}
