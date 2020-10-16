// TwoSum.cpp : Defines the entry point for the console application.
//
#include <bits/stdc++.h>
// #include <stdio.h>
// #include <string.h>

#define TEST_SIZE			100000
// #define PRIME_FACTOR		90017
#define PRIME_FACTOR		12101
#define INPUT_FILE_NAME 	"TestInput_16-10-2020_14H-58M-21S.bin"
// #define USE_INPUT_FILE
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
					// cout << "num [" << nums[i] << ", " << nums[j] << "]"<< endl;
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
		// works for no repetitive numbers
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
					res[0] = ((x.second) -1);
					res[1] = (umap[diff] -1);
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
				/* key is the number and value is the index */
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

short FrameName(char *out_arrcFileName)
{

	time_t S_LocalTime = time(NULL);
    struct tm *S_Time = localtime(&S_LocalTime);

	// pointer validation
	if(out_arrcFileName == NULL)
	{
		return -1;
	}
	else
	{
		//Framing File Name
	    sprintf(out_arrcFileName, "TestInput_%02d-%02d-%02d_%02dH-%02dM-%02dS.bin",
	    		S_Time->tm_mday, S_Time->tm_mon + 1, S_Time->tm_year + 1900,
	    		S_Time->tm_hour, S_Time->tm_min, S_Time->	tm_sec);
	}

    return 0;
}
void readInput(const char *FileName, vector<int> &vec)
{
	FILE *fptr = NULL;
	int iRetVal = 0;
	int iNum = 0;

	if(FileName == NULL)
	{
		printf("Invalid Pointer\n");
	}
	
	fptr = fopen(FileName, "rb");
	if(fptr != NULL)
	{
		while(1)
		{
			iRetVal = fread(&iNum, sizeof(int), 1, fptr);
			if(feof(fptr))
			{
				break;
			}

			vec.push_back(iNum);
		}
		printf("%d data read from %s Success\n", vec.size(), FileName);

		fclose(fptr);
	}
	else
	{
		printf("fopen failed..!\n");
	}
}

void LogInput(vector<int> &vec)
{
	FILE *fptr = NULL;
	int iRetVal = 0;
	char FileName[128] = {0};
	
	FrameName(FileName);
	fptr = fopen(FileName, "wb");
	if(fptr != NULL)
	{
		iRetVal = fwrite(&vec[0], sizeof(int), vec.size(), fptr);
		if(iRetVal != vec.size())
		{
			printf("fwrite failed with return value: %d\n", iRetVal);
		}
		else
		{
			printf("Data logged to %s\n Success", FileName);
		}

		fclose(fptr);
	}
	else
	{
		printf("fopen failed..!\n");
	}
}

void genTestInput(vector <int>& input, int size, int index[2], int *target)
{
	srand(time(NULL));
	int n = 1;
	int step = 0;

	genRandNum(input, size, (size * PRIME_FACTOR));
	// print(input);

	#if 0
		index[0] = (rand() % size);
		if (index[0] < (size - 1))
		{
			index[1] = index[0] + 1;
		}
		else
		{
			index[1] = 0;
		}
		
	#else
		index[0] = size -1;
		index[1] = index[0] -1;
	#endif
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
	
	#ifndef USE_INPUT_FILE
		vector <int> input;
		genTestInput(input, TEST_SIZE, index, &target);
	#else
		vector <int> input;
		readInput(INPUT_FILE_NAME, input);
		index[0] = (input.size() -1);
		index[1] = index[0] -1;	
		target = input[index[0]] + input[index[1]];
	#endif
#else
	vector <int> input = {0, 4, 3, 1};
	index[0] = 0;
	index[1] = 3;
	target = 1;
#endif
	clock_t start_time = clock();

	res = sol.twoSum(input, target);

	cout << "Elapsed time: " << static_cast<double>(clock() - start_time)/CLOCKS_PER_SEC << " seconds" << endl;
	
	if (((res[0] == index[0]) || (res[0] == index[1])) &&
		((res[1] == index[0]) || (res[1] == index[1])) &&
		(res[0] != res[1]))
	{
		cout << "Pass: res [" << res[0] << ", " << res[1] << "]" << endl;
		
		#ifndef USE_INPUT_FILE
			LogInput(input);
		#endif
	}	
	else
	{
		cout << "Fail: res [" << res[0] << ", " << res[1] << "]" << endl;
	}
	
	return 0;
}

