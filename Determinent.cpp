#include<iostream>
#include<vector>
using namespace std;
vector< vector<int> > mat,cf,cf_cpy;
void getMat(int order)
{
	cout<<"Enter a "<<order<<" x "<<order<<" Matrix:"<<endl;
	for(int i = 0; i < order; i++)
	{	
		vector<int> row;
		int elm;
		for(int j = 0; j < order; j++)
		{
			cout<<"elm("<<i+1<<","<<j+1<<") = ";
			cin>>elm;
			row.push_back(elm);
		}
		mat.push_back(row);
		cf_cpy.push_back(row);
	}
}
void clear(int order,vector< vector<int> >& vec)
{
	for(int i = 0; i < order; i++)
		vec.pop_back();
}
void copyCF(int order)
{	clear(order + 1,cf_cpy);
	for(int i = 0; i < order;i++)
	{
		vector<int> row;
		for(int j = 0; j < order; j++)
		{
			row.push_back(cf[i][j]);
		}
		cf_cpy.push_back(row);
	}
	clear(order,cf);
}
int cofactor(int order,int pos,vector< vector<int> >& cofact)
{	
	int val = 0;
	for(int i = 0; i < order + 1; i++)
	{
		vector<int> row;		
		for(int j = 0; j < order + 1; j++)
		{	
			if((i != pos) && (j != pos))
				row.push_back(cofact[i][j]);
		}
		cf.push_back(row);
	}
	copyCF(order);
	if(order == 1)
		val = cf[0][0];
	else if(order == 2)
	{
		val = (cf[0][0] * cf[1][1]) - (cf[0][1] *cf[1][0]);
	}
	else{
		int sign = 1;
		for(int i = 0; i < order; i++)
		{
			val += (sign * cofactor(order-1,i,cf_cpy) * mat[0][i]);
		}
	}
}
int det(int order)
{
	int sign = 1;
	int det;
	if(order == 1)
		return cf_cpy[0][0];
	else if(order == 2)
	{
		return(cf_cpy[0][0] * cf_cpy[1][1]) - (cf_cpy[0][1] *cf_cpy[1][0]);
	}
	for(int i = 0; i < order; i++)
	{
		det += (sign * cofactor(order-1,i,cf_cpy) * mat[0][i]);
		sign *= -1;
	}
	return det;
}
void printMat(int order)
{
	for(int i = 0; i < order; i++)
	{
		for(int j = 0; j < order; j++)
		{
			cout<<mat[i][j]<<" ";
		}
		cout<<endl;
	}
}
int main()
{
	int order;
	cout<<"Determinent of a Matrix"<<endl;
	cout<<"Enter the order of Matrix: ";
	cin>>order;
	getMat(order);
	cout<<"Printing Matrix..."<<endl;
	printMat(order);
	cout<<"Determinent of the given Matrix is "<<det(order)<<endl;
	return 0;
}
