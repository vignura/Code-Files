#include<iostream>
#include<fstream>
using namespace std;
int main()
{
	char base_path[] = "../Desktop/OpenCV/orl_faces/s";
	ofstream wfile("dataset.csv");
	for(int i = 0; i < 40; i++)
	{	for(int j = 0; j < 10; j++)
			wfile<<base_path<<i+1<<"/"<<j+1<<".pgm;"<<i<<endl;
	}
	wfile.close();	
	return 0;
}
