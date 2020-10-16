// TwoSum.cpp : Defines the entry point for the console application.
//
#include <bits/stdc++.h>

#define TEST_SIZE	30
using namespace std;
typedef unordered_multimap<int, int>::iterator umit;


class Solution {
public:
#if 0
	vector<int> twoSum(vector<int>& nums, int target)
	{
		vector<int> res;

		for (int i = 0; i < nums.size(); i++)
		{
			for (int j = i + 1; j < nums.size(); j++)
			{
				if ((nums[i] + nums[j]) == target)
				{
					cout << "num [" << nums[i] << ", " << nums[j] << "]"<< endl;
					res.push_back(i); 
					res.push_back(j);
					return res;
				}
			}
		}

		return res;
	}

#else
	#if 0
		vector<int> twoSum(vector<int>& nums, int target)
		{
			vector<int> res = {0, 0};
			unordered_map <int, int> umap;
			int diff = 0;

			/* create a unordered map with the input vector */
			for (int i = 0; i < nums.size(); i++)
			{
				/* store the index as the value and number as the 
				 key, +1 is added to avoid a collision between the index 0
				 and a out of bound value */
				umap[nums[i]] = (i + 1);			
			}

			/* find the two sum */
			for (auto x: umap)
			{
				diff = (target - x.first);
				
				if(umap[diff] > 0)
				{
					res[0] = x.second;
					res[1] = umap[diff];
				}
			}

			return res;
		}
	#else
		vector<int> twoSum(vector<int>& nums, int target)
		{
			vector<int> res = {0, 0};
			unordered_multimap <int, int> ummap;
			int diff = 0;

			/* create a unordered multimap with the input vector */
			for (int i = 0; i < nums.size(); i++)
			{
				ummap.insert(make_pair(nums[i], i));			
			}

			/* find the two sum */
			for (auto x: ummap)
			{
				/* compute the difference and check 
				   wheather it is present in the map */
				diff = (target - x.first);
				umit it = ummap.find(diff);

				if(it != ummap.end())
				{
					res[0] = (x.second);

					if(x.second == it->second)
					{
						pair<umit, umit> pit = ummap.equal_range(diff);
						pit.first++;
						res[1] = pit.first->second;
					}
					else
					{
						res[1] = it->second;
					}
				}
			}

			return res;
		}
	#endif
#endif

};

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

void genTestInput(vector <int>& input, int size, int index[2], int *target)
{
	srand(time(NULL));
	int n = 1;
	int step = 0;

	genRandNum(input, size, 1000);
	print(input);

	index[0] = (rand() % size);
	if (index[0] < (size - 1))
	{
		index[1] = index[0] + 1;
	}
	else
	{
		index[1] = 0;
	}
	(*target) = input[index[0]] + input[index[1]];

	cout << "size: " << size << " index: [" << index[0] << ", " << index[1] << "] target: " << (*target) << endl;
	cout << "num [" << input[index[0]] << ", " << input[index[1]] << "]"<< endl;
}

int main()
{
	int index[2] = { 0 };
	int target;
	Solution sol;
	vector <int> res;

#if 1
	vector <int> input;
	genTestInput(input, TEST_SIZE, index, &target);
#else
	vector <int> input = {0, 4, 3, 1};
	index[0] = 0;
	index[1] = 3;
	target = 1;
#endif
	res = sol.twoSum(input, target);
	
	if (((res[0] == index[0]) || (res[0] == index[1])) &&
		((res[1] == index[0]) || (res[1] == index[1])) &&
		(res[0] != res[1]))
	{
		cout << "Pass: res [" << res[0] << ", " << res[1] << "]" << endl;
	}
	else
	{
		cout << "Fail: res [" << res[0] << ", " << res[1] << "]" << endl;
	}
	
	return 0;
}

