#include<iostream>
#include<vector>
using namespace std;
int main()
{
long long int terms,x1,x2;
vector<vector<int>> a;
cout<<"Fibonacci series:"<<endl;
cout<<"enter the value of seeds x1 and x2 :";
cin>>x1>>x2;
cout<<"enter the number of terms: ";
cin>>terms;
for(int i=0;i<terms;i++)
{
a.push_back(x1+x2);
x1 = x2;
x2 = a[0][i];
cout<<a[0][i]<<endl;
}
return 0;
}
