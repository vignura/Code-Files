#include<iostream>
#include<cmath>
#include<vector>
using namespace std;
vector<float> vec;
double pi = 22 / 7;
void sine_gen(float f,float a,float fs, float t)
{
int len = fs * t;
float step = 1 / fs;
for(int i=1;i<=len;i++)
{
	vec.push_back(a*sin(2 * pi * f * (i*step)));
}
}
void print(const vector<float>& a)
{
for(int i=0;i<a.size();i++)
{
	cout<<a[i]<<endl;
}
}
int main()
{
float f,a,fs,t;
cout<<"Sine Wave Samples Generator:\nenter the frequency of the wave: ";
cin>>f;
cout<<"enter the amplitude: ";
cin>>a;
cout<<"enter the samplinig frequency: ";
cin>>fs;
cout<<"enter the length of signal in seconds: ";
cin>>t;
sine_gen(f,a,fs,t);
print(vec);
return 0;
}
