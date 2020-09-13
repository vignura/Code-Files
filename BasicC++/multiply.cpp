#include<iostream>
#include<ctime>
using namespace std;
static char a[20000],b[20000];
static int x[20000][20000],a1[20000],b1[20000],num[40000];
static int lena=0,lenb=0,carry=0,count=0;
static long long int sum;
int main()
{
long int i,j,k;
cout<<"Use  'stty -icanon' command to enter more than 4095 digit number \nenter a :"<<endl;
cin.getline(a,20000);
cout<<"enter b :"<<endl;
cin.getline(b,20000);
clock_t start_time = clock();
//find len a
for(int i=0;a[i]!='\0';i++)
{
	lena ++;
}
//cout<<"length of a is "<<lena<<endl;
//find len b
for(int i=0;b[i]!='\0';i++)
{
	lenb ++;
}
//cout<<"length of b is "<<lenb<<endl;
//converting char to int 
for(int i=lena-1,j=0;i>=0;i--,j++)
{
	a1[j]=a[i]-48;
}
for(int i=lenb-1,j=0;i>=0;i--,j++)
{
	b1[j]=b[i]-48;
}
//code for producing the multiply matrix 
//cout<<"Matix:\n"<<endl;
for(int i=0;i<lena;i++)
{
	for(int j=0;j<lenb;j++)
	{
		x[i][j]=(a1[i]*b1[j]);
		cout<<x[i][j]<<" ";
	}
cout<<endl;
}
//cout<<endl;
//evaluating the upper diagonal 
cout<<"evaluating upper diagonal"<<endl;
for(int i=0;i<lenb;i++)
{	
	sum=0;
	cout<<"i = "<<i<<endl;
	for(j=i,k=0;((k < lena)&&(j>=0));j--,k++)
	{	cout<<"j = "<<j<<"\tk = "<<k<<endl;
		sum += x[k][j];
	}
	sum +=carry;
	//cout<<"sum @"<<count<<" "<<sum<<endl;
	carry=sum/10;
	num[count]=sum % 10;
	count++;
	cout<<endl;
}
//evaluating the lower diagonal
//cout<<"count before "<<c<<endl;
cout<<"evaluating lower diagonal"<<endl;
for(int i=1;i<lena;i++)
{	
	sum=0;
	cout<<"i = "<<i<<endl;
	for(j=lenb-1,k=i;k<lena;j--,k++)
	{	cout<<"j = "<<j<<"\tk = "<<k<<endl;
		sum += x[k][j];
	}
	sum +=carry;
	//cout<<"sum @"<<count<<" "<<sum<<endl;
	carry=sum/10;
	num[count]=sum % 10;
	count++;
	cout<<endl;
}
num[count]=carry;
cout<<"a * b :("<<count+1<<" digits)"<<endl;
if(num[count]!=0)
cout<<num[count];
for(int i=count-1;i>=0;i--)
{
cout<<num[i];
}
cout<<endl;
cout << "Elapsed time: "<< static_cast<double>(clock() - start_time)/CLOCKS_PER_SEC<< " seconds" << endl;
return 0;
}
