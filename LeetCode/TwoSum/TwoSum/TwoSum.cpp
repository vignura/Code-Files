// TwoSum.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>

using namespace std;
vector <int> input;

class Solution {
public:
	vector<int> twoSum(vector<int>& nums, int target)
	{
		vector<int> res;

		for (int i = 0; i < nums.size(); i++)
		{
			for (int j = i + 1; j < nums.size(); j++)
			{
				if ((nums[i] + nums[j]) == target)
				{
					res.push_back(i);
					res.push_back(j);
					return res;
				}
			}
		}

		return res;
	}
};

void genTestInput(vector <int>& input, int size, int index[2], int *target)
{
	srand(time(NULL));
	int n = 0;

	cout << "[";
	for (int i = 0; i < size; i++)
	{
		n += (i + (rand() % 2));
		n += i;
		input.push_back(n);
		//input.push_back(i);
		//cout << n << " ";
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
}

#define TEST_SIZE	6000

int main()
{
	int index[2] = { 0 };
	int target;
	Solution sol;
	vector <int> res;

	genTestInput(input, TEST_SIZE, index, &target);
	res = sol.twoSum(input, target);
	
	if ((res[0] == index[0]) && (res[1] == index[1]))
	{
		cout << "Pass: res [" << res[0] << ", " << res[1] << "]" << endl;
	}
	else
	{
		cout << "Fail: res [" << res[0] << ", " << res[1] << "]" << endl;
	}

	return 0;
}

