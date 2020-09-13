#include<iostream>
#include<cmath>
using namespace std;
int main()
{
long int limit,count=1;
cout<<"Enter the limit:";
cin>>limit;
bool countPrime(int);
for(int i=2;i<limit;i++)
{
	if(countPrime(i))
		count++;
}
cout<<"There are "<<count<<" no of primes in the range"<<endl;
return 0;
}
bool countPrime(int n)
{
int lim = sqrt(n);
int i;
for(i=2;i<=lim;i++)
{
	if(n % i == 0)
		return 0;
}
if(lim == i-1)
	return 1;
}
