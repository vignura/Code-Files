#include <bits/stdc++.h>
using namespace std;

typedef unordered_multimap<string, int>::iterator umit;

void genRandNum(vector<int> &num, int size, int limit);
void print(vector<int> &vec);
void genUMap(unordered_multimap<int, int>& umap, vector<int>& num);
void print(unordered_multimap<int, int>& umap);

int main()
{
	unordered_multimap<int, int> umap;
	vector<int> rnum;

	genRandNum(rnum, 10, 10);
	print(rnum);
	genUMap(umap, rnum);
	print(umap);

	// cout << "bound access: " << umap[rnum[0]] << endl;
	// cout << "outbound access: " << umap[18] << endl;

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

void genUMap(unordered_multimap<int, int>& umap, vector<int>& num)
{
	for(int i = 0; i < num.size(); i++)
	{
		umap.insert(make_pair(num[i], i));
	}
}

void print(unordered_multimap<int, int>& umap)
{
	cout << "[";
	for(auto x : umap)
	{
		cout << "("<< x.first << " " << x.second << ") ";
	}	
	cout << "\b]\n";
}
