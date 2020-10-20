#include <iostream>
#include <vector>
#include <unordered_map>

#define TEST_SIZE		10000
#define PRIME_FACTOR 	12101
// #define PRIME_FACTOR 	1201
using namespace std;

// #define USE_INPUT_FILE			
// #define INPUT_FILE_NAME			"TestInput_20-10-2020_13H-43M-06S.bin"
#define INPUT_FILE_NAME			"TestInput_20-10-2020_13H-45M-27S.bin"
// #define THREE_SUM_TEMPLATE
#define THREE_SUM_BRUTE_FORCE
// #define THREE_SUM_HASH_MAP

void genTestInput(vector <int>& input, int size, int index[3], int *target);
void print(vector<int> &vec, int limit);
short FrameName(char *out_arrcFileName);
void readInput(const char *FileName, vector<int> &vec);
void LogInput(vector<int> &vec);
void genRandNum(vector<int> &num, int size, int limit);

class Solution {

public:

#ifdef THREE_SUM_TEMPLATE 
	vector<int> ThreeSum(vector <int> &input, int target)
	{
		vector<int> result = {0, 0, 0};

		result[0] = TEST_SIZE -2;
		result[1] = result[0] -1;
		result[2] = result[1] -1;
	
		return result;
	}
#endif

#ifdef THREE_SUM_BRUTE_FORCE
	vector<int> ThreeSum(vector<int> &input, int target)
	{
		int i, j, k;
		vector<int> result = {0, 0, 0};
		
		cout << "ThreeSum Brute Force\n";

		for(i = 0; i < (input.size() -2); i++)
		{
			for(j = i; j < (input.size() -1); j++)
			{
				for(k = j; k < input.size(); k++)
				{
					if((input[i] + input[j] + input[k]) == target)
					{
						result[0] = i;
						result[1] = j;
						result[2] = k;

						return result;
					}
				}
			}
		}

		return result;
	}
#endif

#ifdef THREE_SUM_HASH_MAP
	vector<int> ThreeSum(vector<int> &input, int target)
	{
		int idiff = 0;
		int i = 0;
		vector<int> rsult = {0, 0, 0};
		unordered_multimap<int, int> ummap;

		/* make a hash map */
		for(i = 0; i < input.size(); i++)
		{
			ummap.insert(make_pair(input[i], i));
		}

		cout << "Three Sum Hashmap\n";
		for(i = 0; i < input.size(); i++)
		{
			idiff = 
		}

		return result;
	}
#endif
};

int main(int argc, char const *argv[])
{
	int index[3] = {0};
	int target = 0;
	vector<int> result;
	int i = 0;
	int j = 0;

	#ifndef USE_INPUT_FILE
		//#define MANUAL_INPUT
		#ifdef MANUAL_INPUT
			vector<int> Input = {1, 2, 3, 4};
			index[2] = (Input.size() -1);
			index[1] = index[2] -1;	
			index[0] = index[1] -1;	
			target = Input[index[0]] + Input[index[1]] + Input[index[2]];	
		#else
			vector<int> Input;
			/* generate input */
			genTestInput(Input, TEST_SIZE, index, &target);
		#endif
	#else
		vector<int> Input;
		readInput(INPUT_FILE_NAME, Input);
		index[0] = (Input.size() -1);
		index[1] = index[0] -1;	
		index[2] = index[1] -1;	
		target = Input[index[0]] + Input[index[1]] + Input[index[2]];
	#endif

	/* print inputs */
	cout << "Input: ";
	print(Input, 10);
	cout << "Index: [" << index[0] << " " << index[1] << " " << index[2] << "]";
	cout << "\tThree Num: [" << Input[index[0]] << " " << Input[index[1]] << " " << Input[index[2]] << "]";
	cout << "\tTarget: " << target << "\tSize: " << Input.size() << endl;

	Solution sol;

	clock_t start_time = clock();
	result = sol.ThreeSum(Input, target);
	cout << "Elapsed time: " << static_cast<double>(clock() - start_time)/CLOCKS_PER_SEC << " seconds" << endl;

	cout << "Result: ";
	print(result, result.size());

	if((result[0] != result[1]) && (result[0] != result[2]) && (result[1] != result[2]))
	{
		for(i = 0; i < 3; i++)
		{
			for(j = 0; j < 3; j++)
			{
				if(result[i] == index[j])
				{
					break;
				}
			}

			/* if j is equal to 3, it means there is no match found */
			if(j == 3)
			{
				break;
			}
		}

		/* if i is than 3 then, there is a mismatch between resutl 
		   and expected value */
		if(i == 3)
		{
			cout << "PASS\n";
			#if !(defined(USE_INPUT_FILE) || defined(MANUAL_INPUT))
				LogInput(Input);
			#endif

			/* added for watch */
			return -1;
		}
		else
		{
			cout << "FAIL\n";
		}
	}
	else
	{
		cout << "FAIL\n";
	}
	
	return 0;
}

void print(vector<int> &vec, int limit)
{
	int i = 0;

	cout << "[";
	for(i = 0; (i < vec.size() && (i < limit)); i++)
	{
		cout << vec[i] << " ";
	}
	
	if(i < vec.size())
	{
		cout << "... ";
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
	int count = 0;
	if(FileName == NULL)
	{
		printf("Invalid Pointer\n");
	}
	
	fptr = fopen(FileName, "rb");
	if(fptr != NULL)
	{
		while(count < TEST_SIZE)
		{
			iRetVal = fread(&iNum, sizeof(int), 1, fptr);
			if(feof(fptr))
			{
				break;
			}

			vec.push_back(iNum);
			count++;
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

void genTestInput(vector <int>& input, int size, int index[3], int *target)
{
	srand(time(NULL));
	int n = 1;
	int step = 0;

	genRandNum(input, size, (size * PRIME_FACTOR));

	#if 0
		index[0] = (rand() % size);
		if (index[0] < (size - 2))
		{
			index[1] = index[0] + 1;
			index[2] = index[1] + 1;
		}
		else
		{
			index[1] = 0;
			index[2] = 1;
		}
		
	#else
		index[0] = size -1;
		index[1] = index[0] -1;
		index[2] = index[1] -1;
	#endif
	(*target) = input[index[0]] + input[index[1]] + input[index[2]];
}
