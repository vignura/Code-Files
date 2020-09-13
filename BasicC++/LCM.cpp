#include<iostream>
using namespace std;
int main()
{
int a,b;
int getLCM(int, int);
cout<<"LCM Finder"<<endl;
cout<<"Enter two numbers: ";
cin>>a>>b;
cout<<"LCM ("<<a<<", "<<b<<") = "<<getLCM(a,b)<<endl;
return 0;
return 0;
}
int getLCM(int a, int b)
{
int LCM,HCF;
int getHCF(int,int);
HCF = getHCF(a,b);
cout<<"HCF ("<<a<<", "<<b<<") = "<<getHCF(a,b)<<endl;
LCM = (a / HCF) * b;
return LCM;
}
//HCF Finding Function
int getHCF(int a, int b)
{
int num,div,rem;
if(a < b){
	div = a;
	num = b;
}
else{ 
	div = b;
	num = a;
}
do{
rem = num % div;
if(rem != 0){
	num = div;
	div = rem;
}
}while(rem != 0);
return div;
}
