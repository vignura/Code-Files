#include<iostream>
using namespace std;
int main()
{
unsigned long long int num,num1;
int a[100],rem,i;
cout<<"enter a number: ";
cin>>num;
num1=num;
for(i=0;num1!=0;i++)
{
	rem = num1 % 2;
	a[i]= rem;
	num1 /=2;
}
cout<<"the binary value:("<<i<<" bit)"<<endl;
for(int j=(i-1);j>=0;j--)
{
	cout<<a[j];
}
cout<<endl;
num1=num;
for(i=0;num1!=0;i++)
{
	rem = num1 % 16;
	a[i]= rem;
	num1 /=16;
}
cout<<"the hexa-decimal value:("<<i<<" bit)"<<endl;
for(int j=(i-1);j>=0;j--)
{	
	if(a[j]<10)
		cout<<a[j];
	switch(a[j])
	{
		case 10:
			{cout<<"A";break;}
		case 11:
			{cout<<"B";break;}
		case 12:
			{cout<<"C";break;}
		case 13:
			{cout<<"D";break;}
		case 14:
			{cout<<"E";break;}
		case 15:
			{cout<<"F";break;}
	}
}
cout<<endl;
return 0;
}
