#include<iostream>
#include<cmath>
using namespace std;

bool isPrime(int);

int main()
{
	long int limit = 0;
	long int count = 1;

	cout << "Enter the limit:";
	cin >> limit;
	
	for(int i = 2; i < limit; i++)
	{
		if(isPrime(i)){
			count++;
		}
	}

	cout << "There are " << count << " no of primes in the range" << endl;
	return 0;
}

bool isPrime(int n)
{
	int lim = sqrt(n);
	int i = 2;

	for(i <= lim; i++)
	{
		if(n % i == 0){
			return 0;
		}
	}

	if(lim == i-1){
		return 1;
	}
}
