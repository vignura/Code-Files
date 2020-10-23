#include <iostream>
#include <list>
#include <ctime>

#define LIST_SIZE		10000
using namespace std;

void print(list<int>& lst, int limit)
{
	int count = 0;
	cout << "[";
	for(auto x : lst)
	{
		if(count >= limit)
		{
			break;
		}
		cout << x << " ";
		count++;
	}

	if(limit < lst.size())	
	{
		cout << "...]\n";
	}
	else
	{
		cout << "\b]\n";
	}
}

void print(list<int>& lst)
{
	cout << "[";
	for(auto x : lst)
	{
		cout << x << " ";
	}	
	cout << "\b]\n";
}

void insert_sorted(list<int>& lst, int num)
{
	list<int>::iterator it = lst.begin();

	if(lst.empty())
	{
		lst.insert(it, num);
	}
	else
	{
		while((it != lst.end()) && ((*it) <= num))
		{
			it++;
		}
		lst.insert(it, num);
	}
}

int main(int argc, char const *argv[])
{
	list<int> lst;

	srand(time(NULL));

	clock_t start_time = clock();

	/* sort on insert */
	for(int i = 0; i < LIST_SIZE; i++)
	{
		insert_sorted(lst, (rand() % (LIST_SIZE * 10)));
	}
	print(lst, 20);
	cout << "sort on insert Elapsed time: " << (((static_cast<double>(clock() - start_time)) / CLOCKS_PER_SEC) * 1000) << " ms" << endl;

	/* insert and then sort */
	start_time = clock();
	for(int i = 0; i < LIST_SIZE; i++)
	{
		lst.push_back(rand() % (LIST_SIZE * 10));
	}
	lst.sort();
	print(lst, 20);
	cout << "insert and then sort Elapsed time: " << (((static_cast<double>(clock() - start_time)) / CLOCKS_PER_SEC) * 1000) << " ms" << endl;

	return 0;
}
