#include <iostream>
#include <stdlib.h>
#include <ctime>

using namespace std;

// #define ENABLE_DEBUG_PRINTS
#define RAND_NUM_LIMIT	100
#define LIST_SIZE 		10
#define MERGE_LIST_TEST_SIZE (LIST_SIZE / 2)

#ifndef ENABLE_DEBUG_PRINTS
#define MERGE_SORT_TEST_SIZE (100000)
#else
#define MERGE_SORT_TEST_SIZE (10)
#endif

void print_list(int *list, int list_size);
void fill_random_numbers(int *list, int list_size);
void bubble_sort(int *list, int list_size);
void merge_lists(int *list1, int list1_size, int *list2, int list2_size);
void merge_lists_test();
void merge_sort(int* list, int size);
void merge_sort_test();
void bubble_sort_test();

int main()
{
	int list[LIST_SIZE] = {0};

	srand(time(0));

	printf("Filling the list with random numbers ...\n");
	fill_random_numbers(list, LIST_SIZE);
	print_list(list, LIST_SIZE);

	printf("Sorting the list with bubble sort ...\n");
	bubble_sort(list, LIST_SIZE);
	print_list(list, LIST_SIZE);	

	bubble_sort_test();
	merge_lists_test();
	merge_sort_test();

	return 0;
}

void print_list(int *list, int list_size)
{
	if((list == NULL)|| (list_size < 1))
	{
		return;
	}

	printf("[ ");
	for (int i = 0; i < list_size; ++i)
	{
		printf("%d ", list[i]);
	}
	printf("]\n");
}

void fill_random_numbers(int *list, int list_size)
{
	if((list == NULL)|| (list_size < 1))
	{
		return;
	}

	// srand(time(0));
	for (int i = 0; i < list_size; ++i)
	{
		list[i] = (rand() % RAND_NUM_LIMIT);
	}
}

void bubble_sort(int *list, int list_size)
{
	if((list == NULL)|| (list_size < 1))
	{
		return;
	}

	for (int i = 0; i < list_size; ++i)
	{
		for (int j = i + 1; j < list_size; ++j)
		{
			if(list[i] > list[j])
			{
				int tmp = list[i];
				list[i] = list[j];
				list[j] = tmp;
			}
		}
	}
}

void merge_lists(int *list1, int list1_size, int *list2, int list2_size)
{	
	/*create a the temp list as large the entire list instead of just
	  creating one of size = list1 + list2 to avoid dynamic allocation
	  of memory*/
	int tmp[MERGE_SORT_TEST_SIZE] = {0};
	int i = 0, j = 0, k = 0;

#ifdef ENABLE_DEBUG_PRINTS
	printf("Merging list 1 [%d] with list 2 [%d]\n", list1_size, list2_size);
	printf("list 1: "); print_list(list1, list1_size);
	printf("list 2: "); print_list(list2, list2_size);
#endif
	// copy the samllest element form to new list
	for(; (i < list1_size) && (j < list2_size); k++)
	{
		if(list1[i] < list2[j])
		{
			tmp[k] = list1[i];
			i++;
		}
		else
		{
			tmp[k] = list2[j];
			j++;
		}
	}
	
	// copy the left over elements from list1
	for (; i < list1_size; i++, k++)
	{
		tmp[k] = list1[i];
	}
	
	// copy the left over elements from list1
	for (; j < list2_size; j++, k++)
	{
		tmp[k] = list2[j];
	}

	// copy the elements back to original lists
	for (i = 0, k = 0; i < list1_size; ++i)
	{
		list1[i] = tmp[k];
		k++;
	}

	for (i = 0; i < list2_size; ++i)
	{
		list2[i] = tmp[k];
		k++;
	}
}

void merge_lists_test()
{
	int list1[MERGE_LIST_TEST_SIZE] = {0};
	int list2[MERGE_LIST_TEST_SIZE] = {0};

	printf("Testing merge_lists ...\n");
	fill_random_numbers(list1, MERGE_LIST_TEST_SIZE);
	fill_random_numbers(list2, MERGE_LIST_TEST_SIZE);
	
	printf("Generating random lists ...\n");
	print_list(list1, MERGE_LIST_TEST_SIZE);
	print_list(list2, MERGE_LIST_TEST_SIZE);
	
	printf("Sorting using bubble sort ...\n");
	bubble_sort(list1, MERGE_LIST_TEST_SIZE);
	bubble_sort(list2, MERGE_LIST_TEST_SIZE);
	print_list(list1, MERGE_LIST_TEST_SIZE);
	print_list(list2, MERGE_LIST_TEST_SIZE);

	printf("Merging lists ...\n");
	merge_lists(list1, MERGE_LIST_TEST_SIZE, list2, MERGE_LIST_TEST_SIZE);
	print_list(list1, MERGE_LIST_TEST_SIZE);
	print_list(list2, MERGE_LIST_TEST_SIZE);
}

void merge_sort(int* list, int size)
{
	int mid =  (size / 2);
	if(size > 1)
	{
		merge_sort(list, mid);
		merge_sort((list + mid), (size - mid));
		merge_lists(list, mid, (list + mid), (size - mid));
	}
}

void bubble_sort_test()
{
	int list[MERGE_SORT_TEST_SIZE] = {0};
	clock_t start_time;

	printf("Testing bubble sort performance ...\n");
	printf("Generating random list of size %d ...\n", MERGE_SORT_TEST_SIZE);
	fill_random_numbers(list, MERGE_SORT_TEST_SIZE);

#ifdef ENABLE_DEBUG_PRINTS
	print_list(list, MERGE_SORT_TEST_SIZE);
#endif
	printf("Sorting using bubble sort ...");

	start_time = clock();
	bubble_sort(list, MERGE_SORT_TEST_SIZE);
	printf("Elapsed time: %f seconds\n", static_cast<double>(clock() - start_time)/CLOCKS_PER_SEC);

#ifdef ENABLE_DEBUG_PRINTS
	print_list(list, MERGE_SORT_TEST_SIZE);
#endif
}

void merge_sort_test()
{
	int list[MERGE_SORT_TEST_SIZE] = {0};
	clock_t start_time;

	printf("Testing merge sort performance ...\n");
	printf("Generating random list of size %d ...\n", MERGE_SORT_TEST_SIZE);
	fill_random_numbers(list, MERGE_SORT_TEST_SIZE);

#ifdef ENABLE_DEBUG_PRINTS
	print_list(list, MERGE_SORT_TEST_SIZE);
#endif
	printf("Sorting using merge sort ...");

	start_time = clock();
	merge_sort(list, MERGE_SORT_TEST_SIZE);
	printf("Elapsed time: %f seconds\n", static_cast<double>(clock() - start_time)/CLOCKS_PER_SEC);

#ifdef ENABLE_DEBUG_PRINTS
	print_list(list, MERGE_SORT_TEST_SIZE);
#endif
}

/*
[2 4 6]  [3 5 7]

compare elements of both lists, and add the samllest element
to the new list and increment the count

i = 0; j = 0; k = 0; [2 < 3] y {i++ [2]}; k++;
i = 1; j = 0; k = 1; [4 < 3] n {j++ [2 3]}; k++;
i = 1; j = 1; k = 2; [4 < 5] y {i++ [2 3 4]}; k++;
i = 2; j = 1; k = 3; [6 < 5] n {j++ [2 3 4 5]}; k++;
i = 2; j = 2; k = 4; [6 < 7] y {i++ [2 3 4 5 6]}; k++;

copy the left over elements from list 1
i = 3; j = 2; k = 5; [i <= 2] [3 <= 2] n; [2 3 4 5 6]

copy the left over elements from list 2
i = 3; j = 2; k = 5; [j <= 2] [2 <= 2] y; [2 3 4 5 6 7]
*/
