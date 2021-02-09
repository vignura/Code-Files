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
	cout << "Palindrome Checker\n";
	cout << "Enter a string: ";
	cin >> str;
	
	if(str == reverse(str))
	{
		cout << str << " is a palindrome\n";
	}
	else
	{
		cout << str << " is not a palindrome\n";
	}
	
	return 0;
}