#include <iostream>
#include <vector>
#include <ctime>
#include<fstream>
using namespace std;
int main()
{
ofstream writefile("Primes.bin", ios::out | ios::binary);
int limit,count=0;
cout<<"Enter the limit:";
cin>>limit;
clock_t start_time = clock();
vector<bool> nonprimes(limit);
nonprimes[0] = nonprimes[1] = true;
for(int i=2;i<limit;i++)
{
	if(!nonprimes[i])
	{
		writefile.write((char*)&i,sizeof(int));
		count++;
		for(int j=2*i;j<limit;j+= i)
		{
			nonprimes[j]=true;
		}
	}
}
cout<<"There are "<<count<<" no of primes with in the limit"<<endl;
cout << "Elapsed time: "<< static_cast<double>(clock() - start_time)/CLOCKS_PER_SEC<< " seconds" << endl;
writefile.close();
return 0;
}
