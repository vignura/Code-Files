#include <stdio.h>
#include <stdlib.h>

void find_union(int *list1, int list1_size, int *list2, int list2_size, int **list_union, int *union_size);
void find_intersection(int *list1, int list1_size, int *list2, int list2_size, int **list_intersection, int *intersection_size);
void print_list(int *list, int list_size);

int main()
{
    // int list1[] = {1, 2, 3};
    // int list2[] = {4, 4};

    // int list1[] = {1, 2, 3};
    // int list2[] = {1, 2, 3};

    int list1[] = {3, 2, 1};
    int list2[] = {3, 4, 5, 6};

    int *list_union = NULL;
    int union_size = 0;

    printf("List 1: ");
    print_list(list1, (sizeof(list1) / sizeof(int)));
    printf("List 2: ");
    print_list(list2, (sizeof(list2) / sizeof(int)));

    find_union(list1, sizeof(list1) / sizeof(int), list2, sizeof(list2) / sizeof(int), &list_union, &union_size);
    printf("Union: ");
    print_list(list_union, union_size);
    free(list_union);

    int *list_intersection = NULL;
    int intersection_size = 0;

    find_intersection(list1, sizeof(list1) / sizeof(int), list2, sizeof(list2) / sizeof(int), &list_intersection, &intersection_size);
    printf("Intersection: ");
    print_list(list_union, intersection_size);
    free(list_intersection);
    
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

// allocates memory for list_union of size  list1_size + list2_size
void find_union(int *list1, int list1_size, int *list2, int list2_size, int **list_union, int *union_size)
{
    int i = 0, j = 0, k = 0;
    (*list_union) = (int*)calloc(sizeof(int), (list1_size + list2_size));

    while((i < list1_size) && (j < list2_size))
    {
        if(list1[i] < list2[j])
        {
            (*list_union)[k] = list1[i++];
        }
        else if(list1[i] > list2[j])
        {
            (*list_union)[k] = list2[j++];
        }
        else
        {
            (*list_union)[k] = list1[i]; // or (*list_union)[k] = list2[j];
            i++; j++;
        }

        k++;
    }

    while(i < list1_size)
    {
        (*list_union)[k++] = list1[i++];
    }

    while(j < list2_size)
    {
        (*list_union)[k++] = list2[j++];
    }

    *union_size = k;
}

void find_intersection(int *list1, int list1_size, int *list2, int list2_size, int **list_intersection, int *intersection_size)
{
    int i = 0, j = 0, k = 0;
    (*list_intersection) = (int*)calloc(sizeof(int), (list1_size + list2_size));

    for(i = 0; i < list1_size; i++)
    {
        for(j = 0; j < list2_size; j++)
        {
            if(list1[i] == list2[j])
            {
                (*list_intersection)[k++] = list1[i];
                break;
            }
        }
    }

    *intersection_size = k;
}