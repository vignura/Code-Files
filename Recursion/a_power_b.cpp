#include <iostream>

using namespace std;

int a_pwr_b(int a, int b)
{
	if(b <= 0)
	{
		return 1;
	}

	return (a_pwr_b(a, (b -1)) * a);
}

int main(int argc, char const *argv[])
{
	int a = 0;
	int b = 0;

	cout << "a ^ b\n";
	cout << "Enter a and b: ";
	cin >> a >> b;
	
	cout << a << " ^ " << b << " = " << a_pwr_b(a, b) << endl;
	
	return 0;
}