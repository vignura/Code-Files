#include<iostream>
using namespace std;
int main()
{
float num;
void to_rational(double);
cout<<"Float to rational converter"<<endl;
cout<<"enter a number: ";
cin>>num;
to_rational(num);
return 0;
}
void to_rational(double num)
{
bool neg = false;
if(num < 0){
	neg = true;
	num *= -1;
}
long long n = num,d = 1;
int count = 0,stop = 1;
double num1 = num - n;
cout<<"int val = "<<n<<"\tfloat val = "<<num1<<endl;
n = num * 1000000;
d = 1000000;
if(neg)
	n *= -1;
cout<<"rational num is ("<<n<<" / "<<d<<")"<<endl;
}
