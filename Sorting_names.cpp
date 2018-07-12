#include<iostream>
#include<cstring>
#define LIM 5
using namespace std;
static char Name[10][20];
//get Name function
void getNames(int limit)
{
	cout<<"Enter "<<limit<<" Names..."<<endl;
	for(int i = 0; i < limit; i++)
	{
		cout<<"Enter name "<<i+1<<" : ";
		cin>>Name[i];
	}
}
//clear function
void clear(char *tmp,int len)
{
	for(int i = 0;i < len; i++)
	{
	tmp[i] = '\0';
	}
}
//swap function
void swap(int a,int b)
{
	char tmp[20];
	//clearing tmp
	clear(tmp,20);
	//tmp = Name[a]
	for(int i = 0;Name[a][i] != 0; i++)
	{
		tmp[i] = Name[a][i];
	}
	//clearing Name[a]
	clear(Name[a],20);
	//Name[a] = Name[b]
	for(int i = 0;Name[b][i] != 0; i++)
	{
		Name[a][i] = Name[b][i];
	}
	//clearing Name[b]
	clear(Name[b],20);
	//Name[b] = tmp
	for(int i = 0;tmp[i] != 0; i++)
	{
		Name[b][i] = tmp[i];
	}
}
//sorting function
void sortNames(int limit)
{
	for(int i = 0; i < limit; i++)
	{
		for(int j = i; j < limit; j++)
		{
			if(Name[i][0] > Name[j][0])
				swap(i,j);
			else if(Name[i][0] == Name[j][0])
			{	
				for(int k = 1; ((Name[i][k] != 0) && (Name[j][k] != 0));k++)
				{	
					if(Name[i][k] > Name[j][k]){
						swap(i,j);
						break;
					}
					if(Name[i][k] < Name[j][k])
						break;
				}
			}
		}
	}
}
//print Function
void printNames(int limit)
{
	cout<<"\tPrinting Sorted Names..."<<endl;
	for(int i = 0; i < limit; i++)
	{
	cout<<Name[i]<<endl;
	}
}
//main function
int main()
{
	cout<<"Sorting Names"<<endl<<endl;
	getNames(LIM);
	cout<<"\n\tSorting..."<<endl<<endl;
	sortNames(LIM);
	printNames(LIM);
	return 0;
}
