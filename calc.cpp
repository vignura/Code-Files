#include<iostream>
#include<calc>
using namespace std;
int main()
{
int a,b,choice;
calc cal;
cout<<"This is my calculator app"<<endl;
cout<<"enter two numbers: ";
cin >> a >> b;
cout<<"MENU:\n1.add\n2.subtract\n3.multiply\n4.divide"<<endl;
cout<<"Enter your choice: ";
cin>>choice;
switch(choice)
{
case 1:cout<<a<<" + "<<b<<" = "<<cal.add(a,b)<<endl;break;
case 2:cout<<a<<" - "<<b<<" = "<<cal.sub(a,b)<<endl;break;
case 3:cout<<a<<" * "<<b<<" = "<<cal.mul(a,b)<<endl;break;
case 4:cout<<a<<" / "<<b<<" = "<<cal.div(a,b)<<endl;break;
default:cout<<"Invalid choice try 1 to 4 next time :)"<<endl;
}
return 0;
}
