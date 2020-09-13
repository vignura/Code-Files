#include <iostream>
using namespace std;
struct Div
{
	int Quotient;
	int Remainder;
};
struct myint
{
	int val;
};
int main()
{
//variables
myint x,y;
//prototypes
Div operator/(myint,myint);
void printDiv(const Div&);
//mycode
cout<<"MY Overloaded '/' Operator"<<endl;
cout<<"Enter two numbers: ";
cin>>(x.val)>>(y.val);
cout<<"Dividing "<<x.val<<" by "<<y.val<<" ..."<<endl;
printDiv((x / y));
return 0;
}
//function defnition for overloaded operator '/'
Div operator/(myint x, myint y)
{
Div res;
res.Quotient = (x.val) / (y.val);
res.Remainder = (x.val) % (y.val);
return res;
}
//function for printing Div datatype
void printDiv(const Div& res)
{
cout<<"Quotient = "<<res.Quotient<<endl;
cout<<"Remainder = "<<res.Remainder<<endl;
}
