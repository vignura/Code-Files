#include<iostream>
#include<fstream>
using namespace std;
class RSA
{
long int d,e,n;
public:
void encrypt(int);
int decrypt(int);
void findKey(int p,int q,int e1);
int findRem(long int num,long int pow,long int mod);
int get_file_size(std::string filename);
};
int main()
{
	int a,p,q,e,len,n;
	char file[10000],ch;
	RSA r;
	cout<<"RSA encryption"<<endl;
	ifstream rf("enc.txt");
	len=r.get_file_size("exc.txt");
	rf.read(file,len);
	ofstream wf("dec.txt");
	cout<<"p= ";
	cin>>p;
	cout<<"q= ";
	cin>>q;
	cout<<"e= ";
	cin>>e;
	r.findKey(p,q,e);
	for(int i=0;i<len;i++)
		{
		n=file[i];
		ch=r.decrypt(n);
		//cout<<n<<endl;	
		wf<<ch;
		}
	wf.close();
	return 0;
}
int RSA::encrypt(int a)
{
	long long int c;	
	c=findRem(a,e,n);
	//cout<<"inside enc"<<" num= "<<a<<" e= "<<e<<" n= "<<n<<endl;
	//cout<<" encrypted number is "<<c<<endl;
	//decrypt(c);
	return c;
}
int RSA::decrypt(int a)
{
	long long int b;
	//cout<<"inside dec"<<" num= "<<a<<" e= "<<e<<" n= "<<n<<endl;
	b=findRem(a,d,n);
	return b;
}
void RSA::findKey(int p,int q,int e1)
{
	long int o,i;
	long long int pdt;	
	e=e1;
	d=0;	
	n=(p*q);
	o=(p-1)*(q-1);
	for(i=1;i<o;i++)
	{	
		pdt=o*i;
		if((pdt+1) % e==0)
		{	
			d=((pdt)+1)/e;
			cout<<"d= "<<d<<endl;
			break;
		}
	}

}
int RSA::findRem(long int num,long int pow,long int mod)
{	
	long int tp,sum=0,comb[2][100],count,pow1=pow;
	long long int rem=1,ncount,rem1=1; 
	for(long int i=0;sum!=pow;i++)
	{	count=i;
		for(long int j=1,tp=1;tp<=pow1;j++)
		{	
			if(pow1==1)
			{
				comb[0][i]=1;
			}			
			tp*=2;
			if(tp<=pow1)
			{
				comb[0][i]=tp;
			}
			
		}
		sum+=comb[0][i];
		pow1-=comb[0][i];
	}
	ncount=count;
	for(long int i=0,tp=1;tp!=comb[0][0];i++)
	{	if(i==0)
		{
			tp=1;
			rem=num;
		}
		else
		{
			tp*=2;
			rem*=rem;
		}
		if(rem>=mod)
			rem %=mod;
		if(comb[0][count]==tp)
		{
			comb[1][count]=rem;
			count--;
		}
	}//for(int i=0;i<=ncount;i++)
		//{cout<<comb[0][i]<<"\t"<<comb[1][i]<<endl;}
	for(long int j=ncount;j>=0;j--)
	{
		rem1 *= comb[1][j];
		if(rem1>mod)
		{
			rem1 %= mod;		
		}
		//cout<<"rem1= "<<rem1<<" comb[1][j]= "<<comb[1][j]<<endl; 
	}
	//cout<<"rem1 before if "<<rem1<<endl;
	if(rem1>=mod)
	{	cout<<"rem1 inside if "<<rem1;
		rem1=rem1 % mod;
	}
	//cout<<"\n"<<rem1<<" mod="<<mod<<endl;
return rem1;
}
int RSA::get_file_size(std::string filename) // path to file
{
    FILE *p_file = NULL;
    p_file = fopen(filename.c_str(),"rb");
    fseek(p_file,0,SEEK_END);
    int size = ftell(p_file);
    fclose(p_file);
    return size;
}
