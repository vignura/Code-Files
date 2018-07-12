#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include <ctime>
using namespace std;
int main()
{
void findsize(long long int);
string line;
long int size,i;
static char filename[20],text1[64],text[64];
bool match;
cout<<"Enter the filename:";
cin>>filename;
ifstream readfile(filename,ios::in|ios::binary|ios::ate);
if(readfile.is_open())
	{	
		size=readfile.tellg();
		readfile.seekg (0, ios::beg);	
		cout<<"filesize = "<<size<<" Bytes"<<endl;
		findsize(size);
		do{	
			ifstream readfile(filename);
			i = 0;
			match = false;
			cout<<"Enter the text to be scanned:";
			cin>>text1;
			clock_t start = clock();
			while (getline(readfile,line))
			{	i++;
				for (int index = 0; index < line.length(); index++){
    					text[index] = line[index];
				}
				text[line.length()] = '\0';
				if(!strcmp(text1,text))
				{	
					clock_t stop = clock();
					cout<<"Match found \n"<<i<<" passpharses scanned in ";
					cout<<static_cast<double>(stop - start)/CLOCKS_PER_SEC<<" seconds"<<endl<<endl;
					match = true;
					break;
				}
			}
			clock_t stop = clock();
			if(!match)
			{
				cout<<i<<" passpharses scanned in ";
				cout<<static_cast<double>(stop - start)/CLOCKS_PER_SEC<<" seconds";
				cout<<"\nThere is no match found in this file"<<endl<<endl;
					
			}
			for(int j=0;j<64;j++)
			{
				text1[j] = '\0';
				text[j] = '\0';
			}
		}while(1);
	}	
else
	cout<<"unable to open the file."<<endl;
return 0;
}
void findsize(long long int l)
{
int i;
double a=0;
long long int kb=1000;
for(i=1;l>=kb;i++)
{
	a=(float)l/kb;
	kb *= 1000; 	
}
i=i-1;
switch(i)
{
case 1:cout<<"filesize = "<<a<<" KB"<<endl;
break;
case 2:cout<<"filesize = "<<a<<" MB"<<endl;
break;
case 3:cout<<"filesize = "<<a<<" GB"<<endl;
break;
default:
	{
		i = i-3;
		if(i>0){
			a = a*i*kb;
			cout<<"filesize = "<<a<<" GB"<<endl;
			}	
	}
}
}
