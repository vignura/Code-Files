#include<iostream>
using namespace std;
void print(const char* a)
{
for(int i = 0; a[i] != 0; i++)
{
cout<<a[i];
}
}
int main()
{
cout<<"print test program"<<endl;
print("helloWorld");
cout<<endl;
return 0;
}
 
