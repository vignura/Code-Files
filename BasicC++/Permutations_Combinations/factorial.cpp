#include <iostream>
#include <cstring>

using namespace std;

int factorial (int limit)
{
	int ret = 1;

	for (int i = 2; i <= limit; i++)
	{
		ret *= i;
	}

	return ret;
}

int main(int argc, char const *argv[])
{
	if (argc < 2)
	{
		cout << "usage: " << argv[0] << " [n]" << endl;
		return 0;
	}

	cout << "factorial of " << argv[1] << " is " << factorial(atoi(argv[1])) << endl;
	return 0;
}