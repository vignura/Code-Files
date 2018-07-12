#include<iostream>
#include "Rational1.h"
using namespace std;
int main()
{
Rational a,b,c;
a.getUserIp("int");
b.getUserIp("float");
c.getUserIp("Rational");
cout<<"a = "<<a.abs()<<"\tb = "<<b.abs()<<"\t";b.print();cout<<"\tc = "<<c.abs()<<endl;
}
