#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <ctime>
#include <algorithm>
/* for segfault handler */
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <execinfo.h>


#define TEST_SIZE		10000
#define PRIME_FACTOR 	12101
// #define PRIME_FACTOR 	1201
using namespace std;
typedef unordered_multimap<int, int>::iterator umit;
typedef unordered_set<int>::iterator usit;
typedef list<vector<int>>::iterator lit;

// #define REMOVE_DUPLICATES_PRINT
// #define THREESUM_PRINT

// #define USE_NUMS_FILE			
#define NUMS_FILE_NAME			"Testnums_20-10-2020_13H-45M-27S.bin"
// #define NUMS_FILE_NAME			"Testnums_20-10-2020_13H-45M-27S.bin"

/* 3sum algo types */
// #define THREE_SUM_BRUTE_FORCE
// #define THREE_SUM_HASH_MAP_1
// #define THREE_SUM_HASH_MAP_2
#define THREE_SUM_SORT

// #define REMOVE_DUPLICATE_VECTOR
#define REMOVE_DUPLICATE_LIST

void genTestnums(vector <int>& nums, int size);
void print(vector<int> &vec);
void print(vector<int> &vec, int limit);
short FrameName(char *out_arrcFileName);
void readnums(const char *FileName, vector<int> &vec);
void Lognums(vector<int> &vec);
void genRandNum(vector<int> &num, int size, int limit);
void print(unordered_multimap<int, int>& umap);

#define SIZE		100

void sigsegv_handler(int signo)
{
	void *array[SIZE];
	int iRetVal;

	printf("\nSegfault: %d\n", signo);
	printf("Stack Trace:\n");
	iRetVal = backtrace(array, SIZE);
	// printf("backtrace returned: %d\n", iRetVal);
	// backtrace_symbols_fd(array, SIZE, STDERR_FILENO);
	backtrace_symbols_fd(array, iRetVal, STDERR_FILENO);
	abort();
}

#pragma push_options
#pragma GCC optimize("Ofast")

class Solution {

public:

#ifdef REMOVE_DUPLICATE_LIST
	void remove_duplicates(vector<vector<int>>& res)
	{
		int count = 0;
		int I = 0;
		int J = 0;
		int K = 0;
		unordered_multiset<int> triplet;
		/* initialize the list */
		list<vector<int>> lres(res.begin(), res.end());
		
		#ifdef REMOVE_DUPLICATES_PRINT
			/* print the list */
			for(auto x : lres)
			{
				cout << K << " ";
				print(x);
				K++;
			}
		#endif

		/* remove recurring tripplets */
		for(lit i = lres.begin(); i != lres.end(); i++)
		{
			J = 0;
			for(lit j = i; j != lres.end(); j++)
			{
				if(i == j)
				{
					continue;
				}

				#ifdef REMOVE_DUPLICATES_PRINT
					cout << "[i j]: [" << I << " "<< J << "]\n";
				#endif

				triplet.clear();
				count = 0;
				
				/* insert the first triplet */
				for(int k = 0; k < (*i).size(); k++)
				{
					triplet.insert((*i)[k]);	
				}
				
				// cout << "for 1\n";
				/* check weather all the elements are
				   present in the set */
				for(int k = 0; k < (*j).size(); k++)
				{
					usit it = triplet.find((*j)[k]);
					if(it != triplet.end())
					{
						triplet.erase(it);
						count++;
					}	
				}

				// cout << "for 2\n";

				if(count == 3)
				{
					#ifdef REMOVE_DUPLICATES_PRINT
						cout << "Removing";
						print(*j);
					#endif
					j = lres.erase(j);
					j--; /* as the element is removed */
				}

				J++;
			}

			I++;
		}

		res.clear();
		res.insert(res.end(), lres.begin(), lres.end());
	}
#endif

#ifdef REMOVE_DUPLICATE_VECTOR
	void remove_duplicates(vector<vector<int>>& res)
	{
		int i, j, k;
		int count = 0;
		unordered_multiset<int> triplet;
		
		/* remove recurring tripplets */
		for(i = 0; i < res.size(); i++)
		{
			for(j = (i +1); j < res.size(); j++)
			{
				#ifdef REMOVE_DUPLICATES_PRINT
					cout << "\n[i j]: [" << i << " " << j << "]\t";
				#endif

				triplet.clear();
				count = 0;
				/* insert the first triplet */
				for(k = 0; k < res[i].size(); k++)
				{
					triplet.insert(res[i][k]);	
				}

				/* check weather all the elements are
				   present in the set */
				for(k = 0; k < res[j].size(); k++)
				{
					usit it = triplet.find(res[j][k]);
					if(it != triplet.end())
					{
						triplet.erase(it);
						count++;
					}	
				}

				/* if count equals to 3, then the 
					second triplet is a duplicate of the first, so 
					remove it from the list */
				#ifdef REMOVE_DUPLICATES_PRINT
					cout << "\tcount: " << count;
				#endif

				if(count == 3)
				{
					#ifdef REMOVE_DUPLICATES_PRINT
						cout << "\tremoving index " << j;
					#endif
					res.erase(res.begin() + j);
					j--; /* as the element is removed */
				}

				#ifdef REMOVE_DUPLICATES_PRINT
					cout << endl;

					for (int x = 0; x < res.size(); x++)
					{
						cout << x << " ";
						print(res[x]);
					}
				#endif
			}
		}
	}
#endif

#ifdef THREE_SUM_BRUTE_FORCE
	vector<vector<int>> ThreeSum(vector<int> &nums)
	{
		int i, j, k;
		vector<int> result = {0, 0, 0};
		vector<vector<int>> res;
	
		cout << "ThreeSum Brute Force\n";

		for(i = 0; i < (nums.size() -2); i++)
		{
			for(j = (i +1); j < (nums.size() -1); j++)
			{
				for(k = (j +1); k < nums.size(); k++)
				{
					if((nums[i] + nums[j] + nums[k]) == 0)
					{
						result[0] = nums[i];
						result[1] = nums[j];
						result[2] = nums[k];

						// return result;
						res.push_back(result);
					}
				}
			}
		}
		// cout << "Size: " << res.size() << " Removing duplicates" << endl;
		remove_duplicates(res);
		return res;
	}
#endif

#ifdef THREE_SUM_HASH_MAP_1
	vector<vector<int>> ThreeSum(vector<int> &nums)
	{
		int diff = 0;
		int count = 0;
		int i, j, k;
		int iTwoSumfound = 0;
		vector<int> result = {0, 0, 0};
		vector<vector<int>> res;
		unordered_multimap<int, int> ummap;

		cout << "Three Sum Hashmap\n";
		if(nums.size() < 3)
        {
            return res;
        }

		/* make a hash map */
		for(i = 0; i < nums.size(); i++)
		{
			ummap.insert(make_pair(nums[i], i));
		}

		#ifdef THREESUM_PRINT
			print(ummap);
		#endif

		for(i = 0; i < (nums.size() -1); i++)
		{
			for(j = (i +1); j < nums.size(); j++)
			{
				diff = -(nums[i] + nums[j]);
				count = ummap.count(diff);

				#ifdef THREESUM_PRINT
					cout << "[i j]: [" << i << " " << j << "]\t";
					cout << "nums: [" << nums[i] << " " << nums[j] << "]\t";
					cout << "diff: " << diff << " \tcount: " << count;
				#endif

				if(count == 1)
				{
					umit it = ummap.find(diff);
					if((it->second != i) && (it->second != j))
					// if(it->second > j)	
					{
						result[0] = nums[i];
						result[1] = nums[j];
						result[2] = it->first;
						res.push_back(result);
						
						#ifdef THREESUM_PRINT
							cout << "\tmatched 1";
						#endif
					}	
				}
				else if (count > 1)
				{
					pair<umit, umit> pit = ummap.equal_range(diff);

					#if 0
						for(int index = 0; index < count; index++)
						{
							if((pit.first->second != i) && (pit.first->second != j))
							{
								result[0] = nums[i];
								result[1] = nums[j];
								result[2] = pit.first->first;
								res.push_back(result);
								
								#ifdef THREESUM_PRINT
									cout << "\tmatched 2";
								#endif
							}
							pit.first++;
						}
					#else
							pit.first++;
							if((pit.first->second != i) && (pit.first->second != j))
							{
								result[0] = nums[i];
								result[1] = nums[j];
								result[2] = pit.first->first;
								res.push_back(result);
								
								#ifdef THREESUM_PRINT
									cout << "\tmatched 2";
								#endif
							}
					#endif
				}
				else
				{
					// do nothing		
				}

				#ifdef THREESUM_PRINT
					cout << endl;
				#endif
			}	
		}

		#ifdef THREESUM_PRINT
			// for (int x = 0; x < res.size(); x++)
			// {
			// 	cout << x << " ";
			// 	print(res[x]);
			// }
		#endif
		// cout << "Size: " << res.size() << " Removing duplicates" << endl;
		remove_duplicates(res);
		return res;
	}
#endif

#ifdef THREE_SUM_HASH_MAP_2
	vector<vector<int>> ThreeSum(vector<int> &nums)
	{
		int diff = 0;
		int count = 0;
		int i, j, k;
		int iTwoSumfound = 0;
		vector<int> result = {0, 0, 0};
		vector<vector<int>> res;
		unordered_multimap<int, int> ummap;

		cout << "Three Sum Hashmap\n";
		if(nums.size() < 3)
        {
            return res;
        }

		/* make a hash map, fill with zeros */
		for(i = 0; i < nums.size(); i++)
		{
			ummap.insert(make_pair(nums[i], 0));
		}

		print(ummap);

		for (umit i = ummap.begin(); i != ummap.end(); i++)
		{
			for (umit j = ummap.begin()++; j != ummap.end(); j++)	
			{
				diff = -((i->first) + (j->first));
				count = ummap.count(diff);

				#ifdef THREESUM_PRINT
					// cout << "[i j]: [" << i << " " << j << "]\t";
					// cout << "nums: [" << nums[i] << " " << nums[j] << "]\t";
					// cout << "diff: " << diff << " \tcount: " << count;
				#endif

				if(count == 1)
				{
					umit k = ummap.find(diff);
					if((i->second + j->second + k->second) < 3)
					{
						result[0] = i->first;
						result[1] = j->first;
						result[2] = k->first;
						res.push_back(result);
						
						/* make all the nodes as visited 
						  so this pair never shows again */
						i->second = 1;
						j->second = 1;
						k->second = 1;
						#ifdef THREESUM_PRINT
							cout << "\tmatched 1";
							print(ummap);
						#endif
					}	
				}
				else if (count > 1)
				{
					pair<umit, umit> pit = ummap.equal_range(diff);
					pit.first++;
					if((i->second + j->second + pit.first->second) < 3)	
					{
						result[0] = i->first;
						result[1] = j->first;
						result[2] = pit.first->first;
						res.push_back(result);
						
						/* make all the nodes as visited 
						  so this pair never shows again */
						i->second = 1;
						j->second = 1;
						pit.first->second = 1;

						#ifdef THREESUM_PRINT
							cout << "\tmatched 2";
							print(ummap);
						#endif
					}
				}
				else
				{
					// do nothing		
				}

				#ifdef THREESUM_PRINT
					// cout << endl;
				#endif
			}	
		}

		#ifdef THREESUM_PRINT
			for (int x = 0; x < res.size(); x++)
			{
				cout << x << " ";
				print(res[x]);
			}
			cout << "Removing duplicates" << endl;
		#endif
		remove_duplicates(res);
		return res;
	}
#endif

#ifdef THREE_SUM_SORT
	vector<vector<int>> ThreeSum(vector<int> &nums)
	{
		int i, j;
		int st, end;
		int a, b, c;
		
		vector<int> result(3, 0);
		vector<vector<int>> res;
		
		sort(nums.begin(), nums.end());

		for(i = 0; i < (nums.size() -2); i++)
		{
			a = nums[i];
			st = i;
			end = (nums.size() -1);

			while(st < end)
			{
				b = nums[st];
				c = nums[end];

				if((a + b + c) == 0)
				{
					result[0] = a;
					result[1] = b;
					result[2] = c;
					res.push_back(result);

					st++;
					end--;
				}
				else if((a + b + c) > 0)
				{
					end--;
				}
				else{
					st++;
				}
			}
		}

		remove_duplicates(res);
		return res;
	}
#endif
};

#pragma pop_options
int main(int argc, char const *argv[])
{
	int i = 0;
	vector<vector<int>> result;
	
	/* initialize a segfault handler */
	signal(SIGSEGV, sigsegv_handler);

	#ifndef USE_nums_FILE
		#define MANUAL_nums
		#ifdef MANUAL_nums
			vector<int> nums = {5,-9,-11,9,9,-4,14,10,-11,1,-13,11,10,14,-3,-3,-4,6,-15,6,6,-13,7,-11,-15,10,-8,13,-14,-12,12,6,-6,8,0,10,-11,-8,-2,-6,8,0,12,3,-9,-6,8,3,-15,0,-6,-1,3,9,-5,-5,4,2,-15,-3,5,13,-11,7,6,-4,2,11,-5,7,12,-11,-15,1,-1,-9,10,-8,1,2,8,11,-14,-4,-3,-12,-2,8,5,-1,-9,-4,-3,-13,-12,-12,-10,-3,6,1,12,3,-3,12,11,11,10};
			// vector<int> nums = {-4,-2,1,-5,-4,-4,4,-2,0,4,0,-2,3,1,-5,0};
		#else
			vector<int> nums;
			/* generate nums */
			genTestnums(nums, TEST_SIZE);
		#endif
	#else
		vector<int> nums;
		readnums(nums_FILE_NAME, nums);
	#endif

	/* print numss */
	cout << "nums: ";
	print(nums, 20);
	
	Solution sol;

	clock_t start_time = clock();
	result = sol.ThreeSum(nums);
	cout << "Elapsed time: " << static_cast<double>(clock() - start_time)/CLOCKS_PER_SEC << " seconds" << endl;

	cout << "Result:\n";
	for (auto res: result)
	{	cout << i++ << " ";
		print(res);	
	}
	
	return 0;
}

void print(vector<int> &vec)
{
	print(vec, vec.size());
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
		cout << "...";
	}

	cout << "]\n";
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
	    sprintf(out_arrcFileName, "Testnums_%02d-%02d-%02d_%02dH-%02dM-%02dS.bin",
	    		S_Time->tm_mday, S_Time->tm_mon + 1, S_Time->tm_year + 1900,
	    		S_Time->tm_hour, S_Time->tm_min, S_Time->	tm_sec);
	}

    return 0;
}

void readnums(const char *FileName, vector<int> &vec)
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

void Lognums(vector<int> &vec)
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

void genTestnums(vector <int>& nums, int size)
{
	srand(time(NULL));
	int n = 1;
	int step = 0;

	genRandNum(nums, size, (size * PRIME_FACTOR));
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
