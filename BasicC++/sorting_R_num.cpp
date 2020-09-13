#include <iostream>
#include "Rational.h"
using namespace std;
int main()
{
void print_array(Rational *array,int len);
Rational array[10];
int lcount = 0,scount = 0,pre = 0,spre = 0;
cout<<"Sorting Rational Numbers"<<endl;
for(int i = 0; i < 10; i++)
{
cout<<"Enter Rnum"<<(i + 1)<<endl;
array[i].getint();
cout<<endl;
}
//printing before sorting
cout<<"The array before sorting"<<endl;
print_array(array,10);
//sorting
for(int i = 0; i < 10; i++)
{
pre = lcount;
spre = scount;
	for(int j = i; j < 10; j++)
	{	
		lcount++;
		if(array[i] > array[j])
		{	
			scount++;
			swap(array[i],array[j]);
		}
	}
pre = lcount - pre;
spre = scount - spre;
cout<<"no of comparisons = "<<pre<<"\tno of swaps = "<<spre<<endl;
}
//printing
cout<<endl;
cout<<"The array after sorting"<<endl;
print_array(array,10);
cout<<"no of comparisons = "<<lcount<<"\tno of swaps = "<<scount<<endl;
return 0;
}
void print_array(Rational *array,int len)
{
for(int i = 0; i < len; i++)
{
array[i].print();
cout<<"\t\t\t"<<array[i].toint()<<endl;
}
}
void swap(Rational &a,Rational &b)
{
Rational tmp;
tmp = a;
a = b;
b = tmp; 
}
