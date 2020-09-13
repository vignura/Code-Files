#include<iostream> 
using namespace std;
int main()
{
int n,x,a,b,base;
cout<<"enter the integer\t";
cin>>n;
cout<<"enter the no. of digits\t";
cin>>x;
cout<<"enter radix\t";
cin>>base;
a = n/base;
b = n%base;
cout<<"the float value is\t"<<a<<b<<"x"<<base<<"^"<<x-1<<"\n";
}


