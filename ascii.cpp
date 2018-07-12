#include<iostream>
using namespace std;
int main()
{
char ch = '\0';
int a = ch;
cout<<" NULL is "<<a<<endl;
ch = ' ';
a = ch;
cout<<"space is "<<a<<endl;
ch = '\n';
a = ch;
cout<<"Enter is "<<a<<endl;
do
{
cout<<"enter a key: ";
cin>>ch;
a=ch;
cout<<" : "<<a<<endl;
}while(ch!='x');
return 0;
}
