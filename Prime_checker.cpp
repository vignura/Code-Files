#include<iostream>
#include<cmath>
#include<ctime>
using namespace std;
int main()
{
	unsigned long long int i,num,mod=0;
	do
	{
		cout<<"Enter a number ";
		cin>>num;
		if(num<0)
		{
			cout<<"enter a positive value!";
		}
	}while(num<0);
	clock_t start_time = clock();
	if((num==2)|(num==3)|(num==5))
	{
		cout<<num<<" is a prime number"<<endl;
		goto exit;
	}
	if((num==0)|(num==1))
	{
		cout<<num<<" is not a prime number"<<endl;
		goto exit;
	}
	if(num%2==0)
	{
		cout<<num<<" is not a prime number as it is divisible by 2"<<endl;
		goto exit;	
	}
	if(num%3==0)
	{
		cout<<num<<" is not a prime number as it is divisible by 3"<<endl;
		goto exit;	
	}
	mod=num-1;
	if(num>144)
		mod=sqrt(num);
	//cout<<"mod = "<<mod;
	for(i=6;i<mod;i += 6)
	{
		if(num%(i-1)==0)
		{
			cout<<num<<" is not a prime number as it is divisible by "<<(i-1)<<endl;
			goto exit;
		}
		if(num%(i+1)==0)
		{
			cout<<num<<" is not a prime number as it is divisible by "<<(i+1)<<endl;
			goto exit;
		}
	}	
	if(i>=mod)
	{
		cout<<num<<" is a prime number"<<" ("<<i<<" , "<<mod<<")"<<endl;
	}
exit:cout << "Elapsed time: "<< static_cast<double>(clock() - start_time)/CLOCKS_PER_SEC<< " seconds" << endl;
return 0;
}
