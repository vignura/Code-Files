#include<iostream>
#include<vector>
using namespace std;
vector<int> b(4);
int len =4;
void feedForward(vector<int>& a)
{
int sum = 0;
for(int i=0;i<4;i++)
{
	for(int j=0;j<4;j++)
	{
		if(i==j)
			sum += (0.5 *a[j]);
		else
			sum += (0.25 * a[j]);
	}
b[i]=sum;
sum = 0;
}
}
int main()
{
char num[4];
vector<int> a(4);
cout<<"enter a "<<len<<" digit number";
cin>>num;
for(int i=0;i<len;i++)
{
a[i]= num[i] - 48;
}
feedForward(a);
cout<<"output from NN:"<<endl;
for(int i=0;i<len;i++)
{
cout<<b[i];
}
cout<<endl;
return 0;
}

