// TwoSum.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <unordered_map>

#define TEST_SIZE	30
using namespace std;
vector <int> input;

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
	vector<int> twoSum(vector<int>& nums, int target)
	{
		vector<int> res;
		vector<int> resnum;
		unordered_map <int, int> umap;
		int diff = 0;

		/* create a unordered map with the input vector */
		for (int i = 0; i < nums.size(); i++)
		{
			umap[nums[i]] = 1;			
		}

		/* find the two sum */
		for (auto x: umap)
		{
			diff = (target - x.first);
			
			if(umap[diff] == 1)
			{
				resnum.push_back(x.first, diff)
			}
		}

		/* find the indices */
		for (int i = 0; i < nums.size(); i++)
		{
			if(resnum[0] == nums[i])
			{
				res.push_back(i);
			}
			else if(resnum[1] == nums[i])
			{
				res.push_back(i);
			}
		}

		return res;
	}
#endif

};

void genTestInput(vector <int>& input, int size, int index[2], int *target)
{
	srand(time(NULL));
	int n = 1;
	int step = 0;

	cout << "[";
	for (int i = 0; i < size; i++)
	{
		//n = (i + step);
		n = pow(1.5, i);
		//n += (i + (rand() % 2));
		input.push_back(n);
		cout << n << " ";
		step++;
	}
	cout << "]\n";

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

	genTestInput(input, TEST_SIZE, index, &target);
	res = sol.twoSum(input, target);
	
	if (((res[0] == index[0]) || (res[0] == index[1])) &&  ((res[1] == index[0]) || (res[1] == index[1])))
	{
		cout << "Pass: res [" << res[0] << ", " << res[1] << "]" << endl;
	}
	else
	{
		cout << "Fail: res [" << res[0] << ", " << res[1] << "]" << endl;
	}
	
	getchar();

	return 0;
}

