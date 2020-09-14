#include<iostream>
using namespace std;

class Flames
{
	char name1[20],name2[20],x[6][6];
	int Fcount,ln1,ln2;
public:
	Flames();
	void getName();
	void strikeOut();
	void flame();
	void display();
};

Flames::Flames()
{
	for(int i=0;i<6;i++)
	{
		for(int j=0;j<6;j++)
		{
			x[i][j]=NULL;
		}
	}
	x[0][0]='F';
	x[1][0]='L';
	x[2][0]='A';
	x[3][0]='M';
	x[4][0]='E';
	x[5][0]='S';
	Fcount=-1;
}
void Flames::getName()
{
	int i,j;
	cout<<"Enter two names: "<<endl;
	cin>>name1>>name2;
	for(i=1;name1[i-1]!=NULL;i++)
	{
		ln1=i;
	}
	for(i=1;name2[i-1]!=NULL;i++)
	{
		ln2=i;
	}
}
void Flames::strikeOut()
{
	int i,j;
	int count=0;
	char a,b;
	for(i=0;i<ln1;i++)
	{
		for(j=0;j<ln2;j++)
		{	
			a=name1[i];
			b=name2[j];	
			if(a>=95)
			{
				a-=32;
			}
			else
				{a+=32;}
			if((b==a)|(b==name1[i]))
			{
				name2[j]='1';
				count++;
				break;
			}
		}	
	}
	Fcount+=(ln1+ln2-(2*count));
}

void Flames::flame()
{
	int i,j,Fcount_tmp=Fcount;
	int k,l;
	for(i=0;i<5;i++)
	{	
		l=0;
		if(Fcount>(5-i))
		{
			Fcount_tmp = Fcount % (6-i);	
		}
		for(k=Fcount_tmp+1;k<(6-i);k++)
		{
			x[l][i+1]=x[k][i];
			l++;
		}
		for(j=0;j<Fcount_tmp;j++)
		{
			x[l][i+1]=x[j][i];
			l++;
		}
	}
}
void Flames::display()
{
	char a = x[0][5];
	switch(a)
	{
		case 'F':{cout<<"Friends"<<endl;break;}
		case 'L':{cout<<"Love"<<endl;break;}
		case 'A':{cout<<"Affection"<<endl;break;}
		case 'M':{cout<<"Marriage"<<endl;break;}
		case 'E':{cout<<"Enemy"<<endl;break;}
		case 'S':{cout<<"Sister"<<endl;break;}
	}
}

int main()
{
	Flames f;
	cout<<"FLAMES"<<endl;
	f.getName();
	f.strikeOut();
	f.flame();
	f.display();
	return 0;
}