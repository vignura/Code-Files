#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
//string reverse function
void strRev(string& str)
{
int size = str.size();
for(int i=0,j=size-1;i<size/2;i++,j--)
{
swap(str[i],str[j]); 
}
}
//main function
int main()
{
string sample;
cout<<"Testing string class"<<endl;
cout<<"enter a string: ";
cin>>sample;
strRev(sample);
cout<<"the reverse of the string is: "<<sample<<endl;
return 1;
}

