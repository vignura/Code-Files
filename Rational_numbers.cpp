#include <iostream>
#include "Rational.h"
using namespace std;
int main()
{
void print_res(Rational &,Rational &,Rational &,char);
Rational a,b,*ptr;
Rational sum,diff,pdt,res,mod;
cout<<"Rational Numbers"<<endl;
cout<<"Enter two Rational numbers: "<<endl;
cout<<"First number:"<<endl;
a.getUserInput();
cout<<"Second number:"<<endl;
b.getUserInput();
sum = a + b; 
print_res(a,b,sum,'+');
diff = a - b;
print_res(a,b,diff,'-');
pdt = a * b;
print_res(a,b,pdt,'*');
res = a / b;
print_res(a,b,res,'/');
mod = a % b;
print_res(a,b,mod,'%');
ptr = &a;
cout<<"abs";a.print();cout<<" = "<<a.abs()<<endl;
cout<<"abs";b.print();cout<<" = "<<b.abs()<<endl;
if(a < 'b')
	cout<<"a is less than b"<<endl;
if(b < a)
	cout<<"b is less than a"<<endl;
if(a > b)
	cout<<"a is greater than b"<<endl;
if(b > a)
	cout<<"b is greater than a"<<endl;
///////
if(a <= b)
	cout<<"a is less than or equal to b"<<endl;
else
	cout<<"b is less than or equal to a"<<endl;
if(a >= b)
	cout<<"a is greater than or equal to b"<<endl;
else
	cout<<"b is greater than or equal to a"<<endl;
if(a == b)
	cout<<"a is equal to b"<<endl;
if(a != b)
	cout<<"a is not equal to b"<<endl;
//////
Rational a1;
a1 = *ptr;
cout<<"Testing += operator"<<endl;
cout<<"a = ";a.print();cout<<endl;
cout<<"b = ";b.print();cout<<endl;
a1 += b;
cout<"a += b is ";a1.print();cout<<endl;
//////
a1 = a;
cout<<"Testing -= operator"<<endl;
cout<<"a = ";a.print();cout<<endl;
cout<<"b = ";b.print();cout<<endl;
a1 -= b;
cout<"a -= b is ";a1.print();cout<<endl;
//////
a1 = a;
cout<<"Testing *= operator"<<endl;
cout<<"a = ";a.print();cout<<endl;
cout<<"b = ";b.print();cout<<endl;
a1 *= b;
cout<"a *= b is ";a1.print();cout<<endl;
//////
a1 = a;
cout<<"Testing /= operator"<<endl;
cout<<"a = ";a.print();cout<<endl;
cout<<"b = ";b.print();cout<<endl;
a1 /= b;
cout<"a /= b is ";a1.print();cout<<endl;
//////
a1 = a;
cout<<"Testing %= operator"<<endl;
cout<<"a = ";a.print();cout<<endl;
cout<<"b = ";b.print();cout<<endl;
a1 %= b;
cout<"a %= b is ";a1.print();cout<<endl;
//////
cout<<"Testing overloaded arithmatic operators"<<endl;
cout<<"Testing overloaded + operator"<<endl;
a1 = a + 1;
a.print();cout<<" + 1 = ";a1.print();cout<<endl;
//////
cout<<"Testing overloaded - operator"<<endl;
a1 = a - 1;
a.print();cout<<" - 1 = ";a1.print();cout<<endl;
//////
cout<<"Testing overloaded * operator"<<endl;
a1 = a * 1;
a.print();cout<<" * 1 = ";a1.print();cout<<endl;
//////
cout<<"Testing overloaded / operator"<<endl;
a1 = a / 2;
a.print();cout<<" / 2 = ";a1.print();cout<<endl;
//////
cout<<"Testing overloaded (%) operator"<<endl;
a1 = a % 2;
a.print();cout<<" % 2 = ";a1.print();cout<<endl;
//////
a1 = a;
cout<<"Testing overloaded ++ operator"<<endl;
a1++;
cout<<"a++ = ";a1.print();cout<<endl;
//////
a1 = a;
cout<<"Testing overloaded -- operator"<<endl;
a1--;
cout<<"a-- = ";a1.print();cout<<endl;
//////
a1 = a;
cout<<"Testing overloaded prefix ++ operator"<<endl;
++a1;
cout<<"a++ = ";a1.print();cout<<endl;
//////
a1 = a;
cout<<"Testing overloaded prefix -- operator"<<endl;
--a1;
cout<<"a-- = ";a1.print();cout<<endl;
return 0;
}
void print_res(Rational &a,Rational &b,Rational &res,char ch)
{
a.print();
switch(ch){
case '+':cout<<" + ";b.print();cout<<" = ";res.print();break;
case '-':cout<<" - ";b.print();cout<<" = ";res.print();break;
case '*':cout<<" * ";b.print();cout<<" = ";res.print();break;
case '/':cout<<" / ";b.print();cout<<" = ";res.print();break;
case '%':cout<<" % ";b.print();cout<<" = ";res.print();break;
}
cout<<endl;
}
