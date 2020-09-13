#include <iostream>
#include "Rational1.h"
using namespace std;
int main()
{
Rational x1(-1),x2(1),x3(0);
int terms;
cout<<"Fibonacci series using Rational class"<<endl;
cout<<"enter the no of terms: ";
cin>>terms;
for(Rational i = 0; i < terms; i++)
{
x3 = x1 + x2;
x1 = x2;
x2 = x3;
cout<<x3.abs()<<endl; 
}
return 0;
}
