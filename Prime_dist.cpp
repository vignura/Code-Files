#include<iostream>
#include<vector>
#include<fstream>
#include<ctime>
using namespace std;
int main()
{
const int len = 50847534;
int prime,unit_digit;
vector<int> a(4);
clock_t start_time = clock();
ifstream file("Primes.bin", ios::in | ios::binary);
for(int i=0;i<len;i++)
{
	file.read((char*)&prime,sizeof(int));
	//cout<<prime<<endl;
	unit_digit = prime % 10;
	switch(unit_digit)
	{
		case 1:{
			a[0] += 1;
			break;}
		case 3:{
			a[1] += 1;
			break;}
		case 7:{
			a[2] += 1;
			break;}
		case 9:{
			a[3] += 1;
			break;}

	}	
}
cout<<"The percentage of primes with unit digit 1 in the ranges of 0 to billion is ("<<a[0]<<") "<<(float)(a[0]/508475.34)<<endl;
cout<<"The percentage of primes with unit digit 3 in the ranges of 0 to billion is ("<<a[1]<<") "<<(float)(a[1]/508475.34)<<endl;
cout<<"The percentage of primes with unit digit 7 in the ranges of 0 to billion is ("<<a[2]<<") "<<(float)(a[2]/508475.34)<<endl;
cout<<"The percentage of primes with unit digit 9 in the ranges of 0 to billion is ("<<a[3]<<") "<<(float)(a[3]/508475.34)<<endl;
file.close();
cout << "Elapsed time: "<< static_cast<double>(clock() - start_time)/CLOCKS_PER_SEC<< " seconds" << endl;
return 0;
}
