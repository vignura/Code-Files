#include <iostream>
#include <cmath>

using namespace std;
double mySqrt(double dNum, double dPrecision);

int main()
{
	double dNum = 0;
	double dSqRoot = 0;

	cout << "SQUARE ROOT FINDER" << "\nenter a number: ";
	cin >> dNum;
	
	dSqRoot = mySqrt(dNum, 0.00001);
	cout << "\nSquareRoot: " << dSqRoot << "\tProduct: "<< (dSqRoot * dSqRoot) << endl;

	return 0;
}

double mySqrt(double dNum, double dPrecision)
{
	int iLoopCnt = 0;
	double dDiff = 0; 
	double dSqRoot = 1;

	do{
		dSqRoot = (dSqRoot + (dNum / dSqRoot)) / 2;
		dDiff = abs((dSqRoot * dSqRoot) - dNum);
		
		// enable for debugging 
		cout << "\n" << dSqRoot << "\t" << dDiff;
		iLoopCnt++;
		
	}while((dDiff > dPrecision) && (iLoopCnt < 30));

	return dSqRoot;
}
