#include<iostream>
#include<vector>
#include<fstream>
#include<ctime>
using namespace std;
int main()
{
int prime=0,count=0;
const int len = 50847534;
int first = 0,last = len-1,mid,num; 
ifstream file("Primes.bin", ios::in | ios::binary);
cout<<"Enter a number to be searched in the list of primes:";
cin>>num;
bool match = false;
clock_t start_time = clock();
clock_t stop;
while(first <= last)
{	
	count++;
	mid = first + (last-first+1)/2;
	file.seekg (mid*sizeof(int), ios::beg);
	//cout<<"count: "<<count<<"  mid = "<<mid<<"  val= "<<prime<<endl;
	file.read((char*)&prime,sizeof(int));
	if(prime == num)
	{	
		stop = clock();
		cout<<"Match found in position "<<mid+1<<" after "<<count<<" iterations"<<endl;
		match = true;
		break;
	}
	else if (prime > num)
		last = mid - 1;
	else 
		first = mid + 1;	
}
if(!match)
{
	stop = clock();
	cout<<"No Match found after "<<count<<" iterations"<<endl;
}
cout << "Elapsed time: "<< static_cast<double>(stop - start_time)/CLOCKS_PER_SEC<< " seconds" << endl;
file.close();
return 0;
}

