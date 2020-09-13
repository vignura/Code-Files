#include<vector>
#include<iostream>
using namespace std;
static vector<int> c;
void rev(vector<int> &vec)
{
	for(int i = 0; i < (vec.size() / 2); i++)
	{
		int tmp = vec[i];
		vec[i] = vec[vec.size() -(1 + i)];
		vec[vec.size() -(1 + i)] = tmp;
	}
}
vector<int>* add(vector<int> &a,vector<int> &b)
{	
	int lim,maxlen;
	int sum,carry = 0;
	if(a.size() > b.size()){
		lim = b.size();
		maxlen = a.size();
	}
	else{
		lim = a.size();
		maxlen = b.size();
	}
	for(int i = 0; i < maxlen; i++)
	{	
		if(i < lim){
			sum = a[a.size() -(1 + i)] + b[b.size() -(1 + i)] + carry;
			c.push_back((sum % 10));
			carry = sum / 10;		
		}
		else if(a.size() > b.size()){
			sum = a[a.size() -(1 + i)] + carry;
			c.push_back((sum % 10));
			carry = sum / 10;
		}
		else{
			sum = b[b.size() -(1 + i)] + carry;
			c.push_back((sum % 10));
			carry = sum / 10;
		} 
	}
	if(carry != 0)
		c.push_back(carry);
	rev(c);
	return &c;
}
void copytoint(vector<int>& vec, char *arr)
{
	for(int i = 0; arr[i] != 0; i++)
	{
		vec.push_back(arr[i] - 48);
	}
}
void print(vector<int>* vec)
{
	for(int i = 0; i < vec->size(); i++)
	{
		cout<<(*vec)[i];
	}
}
int main()
{	
	char a[100],b[100];
	vector<int> a_vec,b_vec;
	vector<int> *c;
	cout<<"enter two numbers: ";
	cin>>a>>b;
	copytoint(a_vec,a);
	copytoint(b_vec,b);
	c = add(a_vec,b_vec);
	cout<<"sum of two numbers is ";print(c);cout<<endl;
	return 0;
}
