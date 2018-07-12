#include<iostream>
#include<ctime>
using namespace std;
int findRem(long int num,long int pow,long int);
int main()
{
unsigned long int num,pow,mod,rem;
cout<<"Remainder finder:"<<endl;
cout<<"enter the number: ";
cin>>num;
cout<<"enter the power: ";
cin>>pow;
cout<<"enter the modulo: ";
cin>>mod;
clock_t start_time = clock();
if(pow==1)
{
	rem=num % mod;
}
else
{
	rem=findRem(num,pow,mod);
}
cout<<num<<" ^ "<<pow<<" mod "<<mod<<" = "<<rem<<endl;
cout << "Elapsed time: "<< static_cast<double>(clock() - start_time)/CLOCKS_PER_SEC<< " seconds" << endl;
return 0;
}
int findRem(long int num,long int pow,long int mod)
{	
	long int tp,sum=0,comb[2][100],count,pow1=pow;
	long long int rem=1,ncount,rem1=1; 
	for(long int i=0;sum!=pow;i++)
	{	count=i;
		for(long int j=1,tp=1;tp<=pow1;j++)
		{	
			if(pow1==1)
			{
				comb[0][i]=1;
			}			
			tp*=2;
			if(tp<=pow1)
			{
				comb[0][i]=tp;
			}
			
		}
		sum+=comb[0][i];
		pow1-=comb[0][i];
	}
	ncount=count;
	for(long int i=0,tp=1;tp!=comb[0][0];i++)
	{	if(i==0)
		{
			tp=1;
			rem=num;
		}
		else
		{
			tp*=2;
			rem*=rem;
		}
		if(rem>=mod)
			rem %=mod;
		if(comb[0][count]==tp)
		{
			comb[1][count]=rem;
			count--;
		}
	}for(long int i=0;i<=ncount;i++)
		{cout<<comb[0][i]<<"\t"<<comb[1][i]<<endl;}
	for(long int j=ncount;j>=0;j--)
	{
		rem1 *= comb[1][j];
		if(rem1>mod)
		{
			rem1 %= mod;		
		}
		//cout<<"rem1= "<<rem1<<" comb[1][j]= "<<comb[1][j]<<endl; 
	}
	//cout<<"rem1 before if "<<rem1<<endl;
	if(rem1>=mod)
	{	cout<<"rem1 inside if "<<rem1;
		rem1=rem1 % mod;
	}
	//cout<<"\n"<<rem1<<" mod="<<mod<<endl;
return rem1;
}
