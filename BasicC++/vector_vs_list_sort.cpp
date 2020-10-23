#include <iostream>
#include <list>
#include <vector>
#include <ctime>
#include <algorithm>

#define TEST_SIZE		100000
#define PRINT_LIMIT		10	

using namespace std;

template <typename T>
void print(T& Type, int limit)
{
	int count = 0;
	cout << "[";
	for(auto x : Type)
	{
		if(count >= limit)
		{
			break;
		}
		cout << x << " ";
		count++;
	}

	if(limit < Type.size())	
	{
		cout << "...]\n";
	}
	else
	{
		cout << "\b]\n";
	}
}

int main(int argc, char const *argv[])
{
	vector<int> vec;
	list<int> lst;
	int num = 0;

	srand(time(NULL));

	cout << "Test size: " <<  TEST_SIZE << endl;

	for(int i = 0; i < TEST_SIZE; i++)	
	{
		num = (rand() % (TEST_SIZE * 10));
		lst.push_back(num);
		vec.push_back(num);
	}

	cout << "sorting list ... ";
	print<list<int>>(lst, PRINT_LIMIT);
	clock_t start = clock();
	lst.sort();
	cout << "elapsed time: " << ((static_cast<double>(clock() -start) * 1000) / CLOCKS_PER_SEC) << " ms" << endl;

	cout << "sorting vector ... ";
	print<vector<int>>(vec, PRINT_LIMIT);
	start = clock();
	sort(vec.begin(), vec.end());
	cout << "elapsed time: " << ((static_cast<double>(clock() -start) * 1000) / CLOCKS_PER_SEC) << " ms" << endl;

	return 0;
}
