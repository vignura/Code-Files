#include <iostream>
using namespace std;
int main()
{
float val;
double find_ln(double);
cout<<"Natural Logarithms"<<endl;
cout<<"enter a value: ";
cin>>val;
cout<<"ln("<<val<<") = "<<find_ln(val)<<endl;
return 0;
}
double find_ln(double num)
{
double pow(double,int);
double a = num - 1;
double ln = 0, val;
int sign = 1;
for(int i = 1; i < 21; i++)
{
	val = (pow(a,i) / i);
	ln += (sign * val);
	sign *= -1;
}
return ln;
}
double pow(double num,int pow)
{
double res = 1;
for(int i = 0; i < pow; i++)
{
	res *= num;
}
return res;
}
