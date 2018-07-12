#include<iostream>
using namespace std;
int main()
{
int shift,count=0;
char pt[1000],ct[1000];
cout<<"enter the plaintext without any spaces:"<<endl;
cin>>pt;
cout<<"enter the shift: "<<endl;
cin>>shift;
cout<<"the encrypted text is:"<<endl;
for(int i=0;pt[i]!=NULL;i++)
{
	ct[i]=pt[i]+shift;
	cout<<ct[i];
	count++;
}
cout<<"\nthe decrypted text is :"<<endl;
for(int i=0;i<count;i++)
{
	pt[i]=ct[i]-shift;
	cout<<pt[i];
}
cout<<endl;
return 0;
}
