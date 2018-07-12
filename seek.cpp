#include<iostream>
#include<fstream>
using namespace std;
int main()
{
static char filename[20],x[101];
int n=100,size;
cout<<"enter the file name: ";
cin>>filename;
ifstream myfile(filename,ios::in|ios::binary|ios::ate);
if(myfile.is_open())
{	
	size=myfile.tellg();
	//cout<<"inside if and file size is "<<size<<endl;
	myfile.seekg (0, ios::beg);	
	while(n>0)
	{	cout<<"inside while and read length is "<<n<<endl;
		myfile.read(x,n);
		for(int i=0;i<n;i++)
		{	
			cout<<x[i];
		}
		size -= 100;
		if((size<100)&&(size>0))
		{
			n=size;
		}
		if(size<=0)
			n=0;
	}
}
else 
	cout<<"unable to open";
return 0;
}


