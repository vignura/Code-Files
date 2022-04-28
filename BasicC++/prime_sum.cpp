#include <iostream>
#include <math.h>

using namespace std;

bool is_prime(int n)
{
	if (n < 2)
	{
		return false;
	}

	//cout << "sqrt: " << n << sqrt(n) << endl;
	for (int i = 2; i <= sqrt(n); i++)
	{
		if (n % i == 0)
		{
			return false;
		}
	}

	return true;
}

void print_primesum_in_range(int n1, int n2)
{
	int sum = 0;

	for (int i = n1; i <= n2; i++)
	{
		if (is_prime(i))
		{
			cout << "is prime: " << i << endl;
			sum += i; 
		}
	}

	cout << "sum: " << sum << endl;
}

int main(int argc, char const *argv[])
{
	print_primesum_in_range(0, 100);
	// cout << "sqrt: " << sqrt(4) << endl;
	return 0;
}