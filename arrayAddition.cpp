#include <iostream>
#include "ArrayAdd.h"
using namespace std;
int num1[] = {4,8,1,0,3,7,9};
int num2[] = {9,2,5};
//
int main()
{	
	ArrayAdd x;
	cout<<"Array Addition"<<endl;
	cout<<"num1 = ";x.print(num1,x.arrlen(num1));cout<<endl;
	cout<<"num2 = ";x.print(num2,x.arrlen(num2));cout<<endl;
	cout<<"length of num1 is : "<<x.arrlen(num1)<<endl;
	cout<<"length of num2 is : "<<x.arrlen(num2)<<endl;
	int *sum; 
	sum = x.addArray(num1,num2);
	cout<<"sum = "<<sum<<endl;
	cout<<"len of sum = "<<x.arrlen()<<endl;
	cout<<"num1 + num2 = ";x.print(sum,x.arrlen());cout<<endl;
	return 0;
}
 
