#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define PRINT_LISTS
// #define PRINT_SWAPS

#define TEST_SIZE       5
#define ALGO_COUNT      4
#define ALGO_NAMES  {"bubble sort", "bubble sort optimized", "selection sort", "insertion sort"}

#define BUBBLE_SORT        0
#define BUBBLE_SORT_OPT    1
#define SELECTION_SORT     2
#define INSERTION_SORT     3

///////////////////////////////////
void fill_random_numbers(int *list, int list_size);
void test_is_list_sorted();
void test_sorting_algo(int algo_type, int *list, int list_size, int *org_list);
void bubble_sort(int *list, int list_size);
void bubble_sort_opt(int *list, int list_size);
void selection_sort(int *list, int list_size);
void insertion_sort(int *list, int list_size);
///////////////////////////////////

int main()
{
    int list[TEST_SIZE];
    int list_test[TEST_SIZE];

    fill_random_numbers(list, TEST_SIZE);

    for(int i = 0; i < ALGO_COUNT; i++)
    {
        memcpy(list_test, list, sizeof(list));
        test_sorting_algo(i, list_test, TEST_SIZE, list);
    }

    return 0;
}

void swap(int *a, int *b)
{
    #ifdef PRINT_SWAPS
        printf("%s: [%d %d]\n", __func__, *a, *b);
    #endif
    int tmp = *a;
    *a = *b;
    *b = tmp;
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
    const int uniformity_factor = 1000;
    const int rand_num_limit = 100;
	static bool is_seeded = false;

	if((list == NULL)|| (list_size < 1))
	{
		return;
	}

	if(!is_seeded)
	{
		srand(time(0));
		is_seeded = true;
	}

	for (int i = 0; i < list_size; ++i)
	{
		list[i] = ((rand() / uniformity_factor) % rand_num_limit);
	}
}

bool is_list_sorted(int *list, int list_size)
{
    int i = 0;
    int diff = 0;
    
    for(i = 0; i < (list_size -1); ++i)
    {
        // use only non zero differences
        if ((list[i + 1] - list[i]) != 0)
        {
            // if diff is 0, then we are finding the first
            // non zero difference in the list so we can
            // assign it without looking for sign
            if(diff == 0)
            {
                diff = (list[i + 1] - list[i]);
            }
            else
            {   
                // current diff and next diff should be of the
                // same sign, if that is the case, multiplying 
                // them should always result in positive number
                // (- * - = +) and (+ * + = +)
                if(diff * (list[i + 1] - list[i]) < 0)
                {
                    // this means sign change, so we can break from the loop
                    return false;
                }
                else
                {
                    diff = (list[i + 1] - list[i]);
                }
            }
        }
    }

    return true;
}

bool is_list_intact(int *orglist, int *list, int list_size)
{
    // copy the original list
    int *local_orglist = (int*)malloc(list_size * sizeof(int));
    memcpy(local_orglist, orglist, list_size * sizeof(int));
    
    for(int i = 0; i < list_size; i++)
    {
        bool match_found = false;

        for(int j =  0; j < (list_size - i); j++)
        {
            if(list[i] == local_orglist[j])
            {
                match_found =  true;
                // remove this element by moving all other 
                // this place
                int k = j;
                while(k < (list_size -i -1))
                {
                    local_orglist[k] = local_orglist[k + 1];
                    k++;
                }

                break;
            }
        }

        if(match_found == false)
        {
            return false;
        }
    }

    free(local_orglist);

    return true;
}

void test_is_list_sorted()
{
    int list[TEST_SIZE] = {0};
    
    printf("%s: testing with array of zeros\n", __func__);
    if(is_list_sorted(list, TEST_SIZE) == true)
    {
        printf("%s: PASS\n", __func__);
    }
    else
    {
        printf("%s: FAIL\n", __func__);
    }

    printf("%s: testing with array of incrementing positive numbers\n", __func__);
    for (int i = 0; i < TEST_SIZE; ++i)
    {
        list[i] = i;
    }
    if(is_list_sorted(list, TEST_SIZE) == true)
    {
        printf("%s: PASS\n", __func__);
    }
    else
    {
        printf("%s: FAIL\n", __func__);
    }

    printf("%s: testing with array of incrementing negative numbers\n", __func__);
    for (int i = 0; i < TEST_SIZE; ++i)
    {
        list[i] = (-TEST_SIZE) + i;
    }
    if(is_list_sorted(list, TEST_SIZE) == true)
    {
        printf("%s: PASS\n", __func__);
    }
    else
    {
        printf("%s: FAIL\n", __func__);
    }


    printf("%s: testing with array of decrementing positive numbers\n", __func__);
    for (int i = 0; i < TEST_SIZE; ++i)
    {
        list[i] = TEST_SIZE -i;
    }
    if(is_list_sorted(list, TEST_SIZE) == true)
    {
        printf("%s: PASS\n", __func__);
    }
    else
    {
        printf("%s: FAIL\n", __func__);
    }

    printf("%s: testing with array of decrementing negative numbers\n", __func__);
    for (int i = 0; i < TEST_SIZE; ++i)
    {
        list[i] = -i;
    }
    if(is_list_sorted(list, TEST_SIZE) == true)
    {
        printf("%s: PASS\n", __func__);
    }
    else
    {
        printf("%s: FAIL\n", __func__);
    }

    printf("%s: testing with array of random numbers \n", __func__);
    fill_random_numbers(list, TEST_SIZE);
    if(is_list_sorted(list, TEST_SIZE) == false)
    {
        printf("%s: PASS\n", __func__);
    }
    else
    {
        printf("%s: FAIL\n", __func__);
    }
}

void test_sorting_algo(int algo_type, int *list, int list_size, int *org_list)
{
    char algoName[][256] = ALGO_NAMES;

    printf("%s: testing %s ... ", __func__, algoName[algo_type]);
    switch(algo_type)
    {
        case BUBBLE_SORT:
            bubble_sort(list, list_size);
            break;

        case BUBBLE_SORT_OPT:
            bubble_sort_opt(list, list_size);
            break;
        
        case SELECTION_SORT:
            selection_sort(list, list_size);
            break;

        case INSERTION_SORT:
            insertion_sort(list, list_size);
            break;

        deafult:
            return;
    }
    
    if(is_list_sorted(list, list_size) && is_list_intact(org_list, list, list_size))
    {
        printf("PASS\n");
    }
    else
    {
        printf("FAIL\n");
    }
}

void bubble_sort(int *list, int list_size)
{
    if((list == NULL)|| (list_size < 1))
    {
        return;
    }

    #ifdef PRINT_LISTS
        printf("\n");
        print_list(list, list_size);
    #endif

    for (int i = 0; i < list_size; ++i)
    {
        for (int j = 0; j < (list_size -1); ++j)
        {
            if(list[j] > list[j +1])
            {
                swap(&list[j], &list[j + 1]);
            }
        }
        #ifdef PRINT_LISTS
            print_list(list, list_size);
        #endif
    }
}

// optimized bubble sort
void bubble_sort_opt(int *list, int list_size)
{
    bool swapped = false;

    if((list == NULL)|| (list_size < 1))
    {
        return;
    }

    #ifdef PRINT_LISTS
        printf("\n");
        print_list(list, list_size);
    #endif

    for (int i = 0; i < list_size; ++i)
    {
        swapped = false;

        for (int j = 0; j < (list_size -1); ++j)
        {
            if(list[j] > list[j +1])
            {
                swap(&list[j], &list[j + 1]);
                swapped = true;
            }
        }

        if(swapped == false)
        {
            break;
        }

        #ifdef PRINT_LISTS
            print_list(list, list_size);
        #endif
    }
}

void selection_sort(int *list, int list_size)
{
    int min_idx = 0;
    // find the smallest number in the list and 
    // put it in the first place, now move the
    // next element and repeat.

    #ifdef PRINT_LISTS
        printf("\n");
        print_list(list, list_size);
    #endif

    for(int i = 0; i < list_size; i++)
    {
        min_idx = i;
        for(int j = i + 1; j < list_size; j++)
        {
            if(list[min_idx] > list[j])
            {
                min_idx = j;
            }
        }

        swap(&list[i], &list[min_idx]);

        #ifdef PRINT_LISTS
            print_list(list, list_size);
        #endif
    }
}

void insertion_sort(int *list, int list_size)
{
    #ifdef PRINT_LISTS
        printf("\n");
        print_list(list, list_size);
    #endif

    for (int i = 0; i < list_size -1; ++i)
    {
        int key =  list[i + 1];
        int j = i;
        // printf("for: i = %d, j = %d key = %d\n", i, j, key);
        while((list[j] > key) && (j >= 0))
        {
            // printf("while: list[j] = %d, j = %d\n", list[j], j);
            list[j + 1] =  list [j];
            j--;
        }
        list[j + 1] = key;

        #ifdef PRINT_LISTS
            print_list(list, list_size);
        #endif
    }
}
