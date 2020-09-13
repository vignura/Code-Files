#include<iostream>
#include<fstream>
using namespace std;
int main()
{
char alpha[26];
char ALPHA[26];
char num[10];
char special[5];
for(int i=0;i<26;i++)
{
	ALPHA[i] = 65+i;
	alpha[i] = 97+i;
	cout<<"\n "<<ALPHA[i]<<"\t"<<alpha[i];
	if(i<10){	
		num[i] = 48+i;
		cout<<"\t"<<num[i];
	}
}
special[0] = '_';
special[1] = '#';
special[2] = '@';
special[3] = '!';
special[4] = '*';
return 0;
}
