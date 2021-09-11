#include <stdio.h>
#include <stdlib.h>

void print_list(int *list, int list_size);
int merge_sort_inv(int *list, int list_size);

int main()
{
    // int list[] = {8, 4, 2, 1};
    int list[] = {3, 1, 2};
    print_list(list, sizeof(list) / sizeof(int));
    printf("Inversion count: %d\n", merge_sort_inv(list, sizeof(list) / sizeof(int)));
    return 0;
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


int merge_lists(int *list1, int list1_size, int *list2, int list2_size)
{
    int i, j;
    int k = 0;
    int inversion_count = 0;
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
            // this is the trick, if list1[i] is greater than list2[j] then, 
            // all the remaining elements in list1 above position i are also
            // going to be greater than list2[j] as list1 and list2 are sorted
            // so the inversion count is (list1_size - i)
            inversion_count += (list1_size - i);
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

    return inversion_count;
}

int merge_sort_inv(int *list, int list_size)
{
    int inversion_count = 0;
    #ifdef PRINT_LISTS
        printf("\nInput\t");
        print_list(list, list_size);
    #endif

    int mid = list_size / 2;
    if(list_size > 1)
    {
        inversion_count += merge_sort_inv(&list[0], mid);
        inversion_count += merge_sort_inv(&list[mid], (list_size -mid));
        inversion_count += merge_lists(&list[0], mid, &list[mid], (list_size -mid));
        #ifdef PRINT_LISTS
            printf("\nSorted\t");
            print_list(list, list_size);
        #endif
    }

    return inversion_count;
}