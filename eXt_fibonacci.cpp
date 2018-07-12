#include<vector>
#include<iostream>
#include<ctime>
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
	c.clear();
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
void assign(vector<int>&a, vector<int>&b)
{
	a.clear();
	for(int i = 0; i < b.size(); i++)
	{
		a.push_back(b[i]);
	}
}
void assign(vector<int>&a, vector<int>*b)
{
	a.clear();
	for(int i = 0; i < b->size(); i++)
	{
		a.push_back((*b)[i]);
	}
}
int main()
{	
	int limit;
	vector<int> seed1_vec,seed2_vec;
	vector<int> *c;
	cout<<"Fibonacci series"<<endl;
	cout<<"enter the no of terms: ";
	cin>>limit;
	seed1_vec.push_back(-1);
	seed2_vec.push_back(1);	
	clock_t start = clock();
	for(int i = 0; i < limit; i++)
	{
		c = add(seed1_vec,seed2_vec);
		assign(seed1_vec,seed2_vec);
		assign(seed2_vec,c);
		cout<<endl;print(c);cout<<endl;
	}
	cout<<"length of the last term: "<<c->size()<<endl;
	cout << "Elapsed time: "<< static_cast<double>(clock() - start)/CLOCKS_PER_SEC<< " seconds" << endl;
	return 0;
}
