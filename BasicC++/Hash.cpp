#include <iostream>
#include <fstream>

#define HASH_SIZE 		16

using namespace std;

int main()
{
	int i = 0;
	char filename[20] = {0};
	char x[HASH_SIZE] = {0};
	char x1[HASH_SIZE] = {0};
	
	/* get file path form user */
	cout << "enter the file name: ";
	cin >> filename;
	ifstream myfile(filename,ios::in|ios::binary|ios::ate);
	
	if(!myfile.is_open())
	{	
		cout << "unable to open " << filename << endl;
		return 0;
	}
	
	cout << filename << " opened successfully" << endl;
	do
	{	
		myfile.read(x, HASH_SIZE);

		/* compute hash */
		for(i = 0; i < HASH_SIZE; i++)
		{	
			x[i] = x[i] ^ x1[i];
			x1[i] = x[i];
		}
		
		cout << "Eof: " << myfile.eof() << endl;
		
	}while(!myfile.eof());
	
	/* print the hash value */
	cout << "Hash: ";
	for(int i = 0; i < HASH_SIZE; i++)
	{	
		cout << x[i];
	}
	cout << endl;

	return 0;
}


