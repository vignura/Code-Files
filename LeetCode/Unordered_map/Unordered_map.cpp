#include <iostream>
#include <unordered_map>
#include <cmath>
#include <vector>

using namespace std;
void genRandNum(vector<int> &num, int size, int limit);
void print(vector<int> &vec);
void genUMap(unordered_map<int, int>& umap, vector<int>& num);
void print(unordered_map<int, int>& umap);

int main()
{
	unordered_map<int, int> umap;
	vector<int> rnum;

	genRandNum(rnum, 10, 97);
	print(rnum);
	genUMap(umap, rnum);
	print(umap);

	cout << "bound access: " << umap[rnum[0]] << endl;
	cout << "outbound access: " << umap[18] << endl;

	return 0;
}

void genRandNum(vector<int> &num, int size, int limit)
{
	srand(time(NULL));
	int rnum = 0;

	for(int i = 0; i < size; i++)
	{
		rnum = (rand() % limit);
		// rnum = i;
		// cout << rnum << " ";
        num.push_back(rnum);    
	}
}

void print(vector<int> &vec)
{
	cout << "[";
	for(int i = 0; i < vec.size(); i++)
	{
		cout << vec[i] << " ";
	}
	cout << "\b]\n";
}

void genUMap(unordered_map<int, int>& umap, vector<int>& num)
{
	for(int i = 0; i < num.size(); i++)
	{
		umap[num[i]] = 1;
	}
}

void print(unordered_map<int, int>& umap)
{
	cout << "[";
	for(auto x : umap)
	{
		cout << "("<< x.first << " " << x.second << ") ";
	}	
	cout << "\b]\n";
}
