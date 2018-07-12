#include<iostream>
using namespace std;
int main()
{
float a = 0;
int b = 5;
for(int i=0;i<10;i++)
{
	a += 0.5;
}
if(a==b)
	cout<<"float "<<a<<" is equal to int "<<b;
else
	cout<<"floating point representation is inaccurate";
return 0;
}
