#include <iostream>
using namespace std;

int main()
{
	double sq = 1;
	double num = 0;
	double diff = 0;
	double precision = 0.00001;

	cout << "SQUARE ROOT FINDER" << "\nenter the number:";
	cin >> num;
	int i = 0;
	do{
		sq = ((sq + (num / sq)) / 2);
		diff = ((sq * sq) - num);
		if(diff < 0)
		{
			diff = -diff;
			// cout << "entered if";
		}	
		cout << "\n" << sq << "\t" << diff;
		i++;
	}while((diff > precision) && (i < 30));

	cout << "\nthe square root of " << num <<" is " << sq <<"\nroot * root = " << (sq*sq) << endl;
	return 0;
}
