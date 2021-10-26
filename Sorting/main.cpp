#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define PRINT_LISTS
// #define PRINT_SWAPS

// #define TEST_SIZE       (1024 * 128)
#define TEST_SIZE       (5)
#define ALGO_COUNT      8
#define ALGO_NAMES  {"bubble sort", "bubble sort optimized", "selection sort", "insertion sort", "merge sort", "quick sort naive", "quick sort lomuto", "quick sort hoare"}

#define BUBBLE_SORT        0
#define BUBBLE_SORT_OPT    1
#define SELECTION_SORT     2
#define INSERTION_SORT     3
#define MERGE_SORT         4
#define QUICK_SORT_NAIVE   5
#define QUICK_SORT_LOMUTO  6
#define QUICK_SORT_HOARE   7

// quick sort partiton types
#define NAIVE_PARTITION    0
#define LOMUTO_PARTITION   1
#define HOARE_PARTITION    2

///////////////////////////////////
void fill_random_numbers(int *list, int list_size);
void test_is_list_sorted();
void test_sorting_algo(int algo_type, int *list, int list_size, int *org_list);
void bubble_sort(int *list, int list_size);
void bubble_sort_opt(int *list, int list_size);
void selection_sort(int *list, int list_size);
void insertion_sort(int *list, int list_size);
void merge_sort(int *list, int list_size);
void quick_sort(int *list, int list_size, int partition_type);
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
    if((list == NULL)|| (list_size < 0))
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
            free(local_orglist);
            return false;
        }
    }

    free(local_orglist);

    return true;
}

bool is_list_intact_bs(int *orglist, int *list, int list_size)
{
    int start = 0;
    int mid = 0;
    int end = 0;
    bool match_found = false;

    unsigned char *removed = (unsigned char*)calloc(sizeof(unsigned char), list_size);
    // for every element in orglist, do a binary search in list and remove the match
    for(int i = 0; i < list_size; i++)
    {
        start = 0;
        end = list_size -1;
        match_found = false;

        // printf("%s: looking for %d, element number %d in original list\n", __func__, orglist[i], (i + 1));
        while(start <= end)
        {
            mid = start + ((end - start) / 2);
            if(orglist[i] == list[mid])
            {
                if(!removed[mid])
                {
                    removed[mid] = 1;
                    match_found = true;
                    break;
                }
                else
                {
                    // need to do a linear serach 
                    // go right 
                    int j = mid + 1;
                    while((j <= end) && (list[j] == list[mid]))
                    {
                        if(!removed[j])
                        {
                            removed[j] = 1;
                            match_found = true;
                            break;
                        }
                        j++;
                    }

                    if(!match_found)
                    {
                        // if match still not found go left 
                        j = mid - 1;
                        while((j >= start) && (list[j] == list[mid]))
                        {
                            if(!removed[j])
                            {
                                removed[j] = 1;
                                match_found = true;
                                break;
                            }
                            j--;
                        }

                        if(match_found)
                        {
                            break;
                        }
                    }
                    else
                    {
                        break;
                    }
                }
            }
            else if(orglist[i] < list[mid])
            {
                end = mid -1;
            }
            else
            {
                start = mid + 1;
            }
        }

        if(!match_found)
        {
            free(removed);
            return false;
        }
    }
    free(removed);
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

        case MERGE_SORT:
            merge_sort(list, list_size);
            break;

        case QUICK_SORT_NAIVE:
            quick_sort(list, list_size, NAIVE_PARTITION);
            break;

        case QUICK_SORT_LOMUTO:
            quick_sort(list, list_size, LOMUTO_PARTITION);
            break;

        case QUICK_SORT_HOARE:
            quick_sort(list, list_size, HOARE_PARTITION);
            break;

        default:
            return;
    }
    
    if(is_list_sorted(list, list_size) && is_list_intact_bs(org_list, list, list_size))
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

void merge_lists(int *list1, int list1_size, int *list2, int list2_size)
{
    int i, j;
    int k = 0;
    int *tmp_list = (int*)calloc(sizeof(int), (list1_size + list2_size));

    for(i = 0, j = 0; (i < list1_size) && (j < list2_size); k++)
    {
        if(list1[i] < list2[j])
        {
            tmp_list[k] = list1[i];
            i++;
        }
        else
        {
            tmp_list[k] = list2[j];
            j++;
        }
    }

    // copy the remaining elements form list 1 if any to the back of list
    for(; i < list1_size; i++, k++)
    {
        tmp_list[k] = list1[i];
    }

    // copy the remaining elements form list 1 if any to the back of list
    for(; j < list2_size; j++, k++)
    {
        tmp_list[k] = list2[j];
    }

    // copy the sorted elements back to original list
    k = 0;
    for(i = 0; i < list1_size; i++, k++)
    {
        list1[i] = tmp_list[k];
    }

    for(j = 0; j < list2_size; j++, k++)
    {
        list2[j] = tmp_list[k];
    }

    free(tmp_list);
}

void merge_sort(int *list, int list_size)
{
    #ifdef PRINT_LISTS
        printf("\nInput\t");
        print_list(list, list_size);
    #endif

    int mid = list_size / 2;
    if(list_size > 1)
    {
        merge_sort(&list[0], mid);
        merge_sort(&list[mid], (list_size -mid));
        merge_lists(&list[0], mid, &list[mid], (list_size -mid));
        #ifdef PRINT_LISTS
            printf("\nSorted\t");
            print_list(list, list_size);
        #endif
    }
}

int naive_partition(int *list, int list_size)
{
    int *tmp_list = (int*)calloc(sizeof(int), list_size);
    // choose the last element as the pivot
    int pivot = list[list_size -1];
    int pivot_pos = 0;
    int index = 0;

    // copy all the samller numbers
    for(int i = 0; i < list_size; i++)
    {
        if(list[i] < pivot)
        {
            tmp_list[index++] = list[i];
        }
    }

    // copy the pivot
    pivot_pos = index;
    tmp_list[index++] = pivot;

    // copy all the larger numbers
    for(int i = 0; i < list_size; i++)
    {
        if(list[i] >= pivot)
        {
            tmp_list[index++] = list[i];
        }
    }
    
    // copy the temp array back to the original array
    for(int i = 0; i < list_size; i++)
    {
        list[i] = tmp_list[i];
    }

    if(tmp_list != NULL)
    {
        free(tmp_list);
    }

    return pivot_pos;
}

int lomuto_partition(int *list, int list_size)
{
    int pivot = list[list_size -1];
    int pivot_pos = 0;
    int index = 0;

    for(int i = 0; i < list_size -1; i++)
    {
        if(list[i] <= pivot)
        {
            swap(&list[i], &list[index]);
            index++;
        }
    }
    
    pivot_pos = index;
    swap(&list[index], &list[list_size -1]);

    return pivot_pos;
}

int hoare_partition(int *list, int list_size)
{
    int pivot = list[0];
    int pivot_pos = 0;
    int i = 0;
    int j =  list_size -1;

    while(true)
    {
        while(list[i] < pivot)
        {
            i++;
        }

        while(list[j] > pivot)
        {
            j--;
        }

        if(i >= j)
        {
            pivot_pos = j;
            break;
        }

        swap(&list[i], &list[j]);
    }

    return pivot_pos;
}

void quick_sort(int *list, int list_size, int partition_type)
{
    #ifdef PRINT_LISTS
        printf("\nInput\t");
        print_list(list, list_size);
    #endif

    if(list_size > 1)
    {
        int pivot = 0;
        switch(partition_type)
        {
            case NAIVE_PARTITION:
                pivot = naive_partition(list, list_size);
                break;

            case LOMUTO_PARTITION:
                pivot = lomuto_partition(list, list_size);
                break;

            case HOARE_PARTITION:
                pivot = hoare_partition(list, list_size);
                break;

            default:
                return;
        }
        
        // index - [ 0 1 2 3 4 ]
        // array - [ 1 2 3 4 5 ]
        // pivot         |
        quick_sort(list, pivot, partition_type);
        quick_sort(&list[pivot +1], (list_size -pivot -1), partition_type);
        #ifdef PRINT_LISTS
            printf("\nSorted\t");
            print_list(list, list_size);
        #endif
    }
}