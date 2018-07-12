#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;
class Xor
{
	int size,n,percent,size1;
	char a[100001],ch,a1[100];
	char filename[25];
	long double prog,status;
	int len,sum;
	public:
	void encrypt();
	void decrypt();
	void sort();
	void findLen();
};
void Xor::findLen()
{
	for(int i=0;a1[i]!=0;i++)
	{
		len=i;
		//cout<<"len = "<<len<<endl;	
	}
	sum=0;
	for(int i=0;i<=len;i++)
	{
		sum += a1[i];
	}
	sum /=(len+1);
}
void Xor::encrypt()
{	
	char ofile[100];
	n=100000;
	prog=0;
	percent=1;
	cout<<"?:?:? ";
	cin>>ofile;
	char epath[] = "/home/vignesh/Desktop/.enc/";
	strcat(epath,ofile);
	ofstream writefile(epath);
	cout<<"Encryption mode:\nenter a file name: ";
	cin>>filename;
	ifstream readfile(filename,ios::in|ios::binary|ios::ate);
	if(readfile.is_open())
	{	
		size=readfile.tellg();
		size1=size;
		readfile.seekg (0, ios::beg);	
		cout<<"file size = "<<size<<" Bytes"<<endl;
		if(size<100000)
			n=size;
		cout<<"set a encryption key : ";
		cin>>a1;
		findLen();
		while(n>0)
		{	prog+=n;
			readfile.read(a,n);
			for(int i=0;i<n;i++)
			{	
				sort();
				ch = a1[(i%len)] ^ a[i];
				writefile<<(ch);
				//cout<<a[i];
			}
			size -= n;
			if((size<n)&&(size>0))
			{
				n=size;
			}
			if(size<=0)
				n=0;
			status=(prog*100)/size1;
			if(status>=percent)
			{
				cout<<status<<" % completed"<<endl;
				percent++;
			}
		}
		cout<<"Encrypted"<<endl;
		writefile.close();
		readfile.close();
	}
	else 
		cout<<"unable to open the file"<<endl;
}
void Xor::decrypt()
{	
	n=100000;
	char ifile[100];
	prog=0;
	percent=1;
	cout<<":?:?:";
	cin>>ifile;
	char dpath[]="/home/vignesh/Desktop/.enc/";
	strcat(dpath,ifile);
	ofstream writefile("/home/vignesh/Desktop/.dec/decrypt.txt");	
	ifstream readfile(dpath,ios::in|ios::binary|ios::ate);
	size=readfile.tellg();
	size1=size;
	readfile.seekg (0, ios::beg);	
	cout<<size<<" Bytes"<<endl;
	cout<<"decryption mode:\nenter the key: ";
	cin>>a1;	
	findLen();
	if(size<100000)
		n=size;
	while(n>0)
	{	
		prog+=n;
		readfile.read(a,n);
		for(int i=0;i<n;i++)
		{	
			sort();
			ch = a1[(i%len)] ^ a[i];
			writefile<<(ch);
			//cout<<ch;
		}
			size -= n;
		if((size<n)&&(size>0))
		{
			n=size;
		}
		if(size<=0)
			n=0;
		status=(prog*100)/size1;
		if(status>=percent)
			{
				cout<<status<<" % completed"<<endl;
				percent++;			
			}
	}
	cout<<"Decrypted"<<endl;
	writefile.close();
	readfile.close();
}
void Xor::sort()
{
	for(int j=1;j<=len;j++)
	{
		a1[j]=sum+(a1[j-1]-a1[j]);
	}
	char ch=a1[0];
	for(int j=0;j<len;j++)
	{
		a1[j]=a1[j+1];
		//cout<<a1[j];
	}
	a1[len]=ch;	
	//cout<<a1[len]<<endl;
}
int main(int arg1, char* arg[])
{
	Xor x;
	if(arg[1][0]=='e')
	{
		x.encrypt();
	}	
	else if(arg[1][0]=='d')
	{
		x.decrypt();
	}
	else
	return 0;
}
