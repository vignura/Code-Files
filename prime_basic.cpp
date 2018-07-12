#include<iostream>
#include<cmath>
#include<ctime>
#include "Rational.h"
using namespace std;
int main()
{
Rational Rnum;
bool Prime(Rational);
cout<<"PrimeTester"<<endl;
cout<<"Enter a Rational Number"<<endl;
Rnum.getint();
clock_t start_time = clock();
if(Prime(Rnum))
	cout<<Rnum.abs()<<" is a Prime number"<<endl;
else
	cout<<Rnum.abs()<<" is not a Prime number"<<endl;
cout << "Elapsed time: "<< static_cast<double>(clock() - start_time)/CLOCKS_PER_SEC<< " seconds" << endl;
return 0;
}

bool Prime(Rational Rnum)
{
/*if(!Rnum.is_int())
	return false;*/ // no need to use this condition when getint() function is used
if(Rnum < 2)			
	return false;
if((Rnum != 2) && ((Rnum % 2) == 0))
	return false;
for(Rational i(3,1); i <= sqrt(Rnum.abs()); i += 2)	 								
{	
	if(((int)Rnum.abs() % (int)i.abs()) == 0)
		return false;
}
return true;
}


