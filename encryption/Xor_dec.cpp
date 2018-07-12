#include<iostream>
#include<fstream>
#include<string>
using namespace std;
int get_file_size(std::string filename);
int main()
{
int n;
char a[1000000],ch=80,a1[10];
ifstream readfile("enc.txt");
ofstream writefile("dec.txt");
n=get_file_size("enc.txt");
cout<<n<<endl;
readfile.read(a,n);
cout<<"enter the key: ";
cin>>a1;
for(int i=0;i<10;i++)
{
	for(int j=0;j<10;j++)
	{	
		char c;
		if(a1[i]>a1[j])
		{
			c=a1[i];
			a1[i]=a1[j];
			a1[j]=c;
		}
	}
}
for(int i=0;i<n;i++)
{
ch = a1[(i%10)] ^ a[i];
writefile<<(ch);
cout<<ch;
ch=a1[0];
for(int j=0;j<9;j++)
{
	a[i]=a[i+1];
}
a1[9]=ch;
}
return 0;
}
int get_file_size(std::string filename) // path to file
{
    FILE *p_file = NULL;
    p_file = fopen(filename.c_str(),"rb");
    fseek(p_file,0,SEEK_END);
    int size = ftell(p_file);
    fclose(p_file);
    return size;
}
