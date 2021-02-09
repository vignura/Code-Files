#include <iostream>

using namespace std;

string reverse(string str)
{
	if(str.length() < 2)
	{
		return str;
	}

	return reverse(str.substr(1, str.length())) + str[0];
}

int main(int argc, char const *argv[])
{
	string str;
	cout << "Reverse a String\n";
	cout << "Enter a string: ";
	cin >> str;
	cout << reverse(str) << endl;
	return 0;
}