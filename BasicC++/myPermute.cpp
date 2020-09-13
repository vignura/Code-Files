#include<iostream>
#include<ctime>
#include<vector>
#include<algorithm>
using namespace std;
//print function
void print(vector<char>& a)
{
for(int i=0;i<a.size();i++)
{
	cout<<a[i];
}
cout<<endl;
}
//permute function
void myPermute(vector<char>& a)
{
int size = a.size();
for(int i=0;i<size;i++)
{
	for(int j=0;j<size-1;j++)
	{
		swap(a[j],a[j+1]);
		print(a);
	}
}
}
//main function
int main()
{
char ch[20];
vector<char> a;
cout<<"MyPermute Function"<<endl<<"enter the initial vector: ";
cin>>ch;
for(int i=0;ch[i]!='\0';i++)
{
	a.push_back(ch[i]);
}
myPermute(a);
return 0;
}
