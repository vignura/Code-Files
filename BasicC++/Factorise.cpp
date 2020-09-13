#include<iostream>
#include "Factorise.h"
using namespace std;
int main()
{
int num;
int* array;
Fact fact;
cout<<"enter a number: ";
cin>>num;
cout<<"factorising..."<<endl;
fact.factorise(num);
array = fact.factors();
for(int i = 0; i < fact.len(); i++)
{
cout<<array[i]<<endl;
}
cout<<"Loop Count = "<<fact.getLoopCount()<<endl;
return 0;
}

