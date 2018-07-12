#include<iostream>
#include<fstream>
using namespace std;
int main()
{
static char filename[20],x[16],x1[16];
int n=16,size;
cout<<"enter the file name: ";
cin>>filename;
ifstream myfile(filename,ios::in|ios::binary|ios::ate);
for(int i=0;i<16;i++)
{
	x1[i]=0;
}
if(myfile.is_open())
{	
	size=myfile.tellg();
	myfile.seekg (0, ios::beg);	
	while(n>0)
	{	//cout<<"inside while and read length is "<<n<<endl;
		myfile.read(x,n);
		for(int i=0;i<n;i++)
		{	
			x[i]=x[i]^x1[i];
			x1[i]=x[i];
		}
		size -= 16;
		if((size<16)&&(size>0))
		{
			n=size;
			for(int i=size;i<16;i++)
			{
				x[i]=0;
			}
		}
		if(size<=0)
			n=0;
	}
	cout<<"the hash value:"<<endl;
	for(int i=0;i<16;i++)
	{	
		int a;
		a=x[i];
		cout<<a;
	}
	cout<<endl;
}
else 
	cout<<"unable to open";
return 0;
}


