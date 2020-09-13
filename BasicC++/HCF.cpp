#include<iostream>
using namespace std;
int main()
{
int a,b;
int getHCF(int, int);
cout<<"HCF Finder"<<endl;
cout<<"Enter two numbers: ";
cin>>a>>b;
cout<<"HCF ("<<a<<", "<<b<<") = "<<getHCF(a,b)<<endl;
return 0;
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
void print(int *array,int len)
{
for(int i = 0; i < len; i++)
{
cout<<array[i]<<endl;
}
}
