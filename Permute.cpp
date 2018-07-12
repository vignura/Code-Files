#include<iostream>
#include<ctime>
#include<algorithm>
#include<vector>
#include<fstream>
using namespace std;
static int c = 0;
ofstream outfile("wordlist.lst");
void print(const vector<char>& a) {
c++;
int n = a.size();
if (n > 0) {
for (int i = 0; i < n; i++)
outfile<< a[i]; // Print the rest
}
outfile<<endl;
}
void permute(vector<char>& a, int begin, int end) {
if (begin == end) {
print(a);
}
else {
for (int i = begin; i <= end; i++) {
swap(a[begin], a[i]);
permute(a, begin + 1, end);
swap(a[begin], a[i]);
}
}
}
int main()
{
char ch[20];
vector<char> initial;
cout<<"enter the initial vector:";
cin>>ch;
for(int i=0;ch[i]!='\0';i++)
{
	initial.push_back(ch[i]);
}
clock_t start = clock();
permute(initial,0,(initial.size()-1));
cout<<"count = "<<c<<endl;
cout<<"Time Elasped: "<<static_cast<double>(clock() - start)/CLOCKS_PER_SEC<<" seconds"<<endl;
return 0;
}
