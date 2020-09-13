#include <list>
#include <stdio.h>
#include <cstdlib>
#include <ctime>

using namespace std;
void print_list(list<int> l);
void insert_in_order(list<int> &l, int num);
void insert_in_order_b(list<int> &l, int num);

#define LIMIT		500000

int main()
{
	int num = 0;
	list<int> l;
	list<int> l1;
	srand(time(NULL));

	for(int i = 0; i < LIMIT; i++)
	{
		// num = rand() % LIMIT;
		num = rand() % LIMIT;
		l.push_front(num);
		// l1.push_back(num);
		// insert_in_order(l, num);
	}
	l.sort();
	// print_list(l);
	// print_list(l1);
}

void print_list(list<int> l)
{
	printf("[ ");
	for(list<int>::iterator it = l.begin(); it != l.end(); it++)
	{
		printf("%d ", *it);
	}
	printf("]\n");
}

void insert_in_order(list<int> &l, int num)
{
	list<int>::iterator it = l.begin();

	// find and insert 
	for(; it != l.end(); it++)
	{
		if(*it > num)
		{
			break;
		}
	}
	
	l.insert(it, num);
}

void insert_in_order_b(list<int> &l, int num)
{
	list<int>::iterator it = l.begin();
	int len = l.size();
	int dir = 1;
	int mid = 0;

	// find and insert 
	while(len > 0)
	{
		mid = ((len / 2) + 1);

		for(int i = 0; i < mid; i++)
		{
			if(dir)
			{
				it++;
			}
			else
			{
				it--;
			}
		}

		if(*it > num)
		{
			break;
		}
		else
		{

		}
	}
	
	l.insert(it, num);
}