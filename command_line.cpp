#include<iostream>
using namespace std;
int main(int argc, char * arg[])
{
for(int i=0;i<argc;i++)
{
	cout<<"The argument no "<<i<<" is "<<arg[i]<<endl;
}
return 0;
}
