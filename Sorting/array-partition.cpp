// [7 6 1 7] total sum = (21 / 3) = 7
// [13 8 14; 7 13; 7]
// 

// [1 3 6 2 7 1 2 8] total sum = (30 / 3) = 10
// [4 7 3 8 2 3 9; 9 5 10 4 5 12; 8 13 7 8 14; 9 3 4 10; 8 9 15; 3 9; 10]

#include <stdio.h>
#include <stdlib.h>

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

bool find_next_segment(int seg_sum, int *list, int size, int *seg_pos)
{
    int sum = 0;
    // next segment should have atleast one element
    // that's why size -1
    for(int i = 0; i < size -1; i++)
    {
        sum += list[i];
        if(sum == seg_sum)
        {
            *seg_pos = i + 1;
            return true;
        }
    }

    printf("seg_sum: %d list_size: %d seg_pos: %d\n", seg_sum, size, *seg_pos);
    printf("list: "); 
    print_list(list, size);

    return false;
}

void partition_to_three_equal_parts(int *list, int size)
{
    int list_sum = 0;
    int seg_sum = 0;
    int seg_2_pos = -1;
    int seg_3_pos = -1;

    printf("%s\n", __func__);

    // calculate the sum of whole list
    for(int i = 0; i < size; i++)
    {
        list_sum += list[i];
    }

    // check if it is divisible by three
    if(list_sum % 3 == 0)
    {
        seg_sum = list_sum / 3;
        // find first segment
        if(find_next_segment(seg_sum, list, size, &seg_2_pos))
        {
            // find second segment
            if(find_next_segment(seg_sum, &list[seg_2_pos], size - seg_2_pos, &seg_3_pos))
            {
                seg_3_pos += seg_2_pos;
                // not calculating the third segments sum as it should be equal to seg_sum since the total sum
                // print the segments
                printf("segment 1: ");
                print_list(list, seg_2_pos);
                printf("segment 2: ");
                print_list(&list[seg_2_pos], (seg_3_pos - seg_2_pos));
                printf("segment 3: ");
                print_list(&list[seg_3_pos], (size - seg_3_pos));
                return;
            }
        }
    }

    printf("list cannot be partitioned into 3 equal sum parts !\n");
}

void partition_to_equal_parts(int partition_size, int *list, int size)
{
    int list_sum = 0;
    int seg_sum = 0;
    int seg_count = 0;
    int *seg_pos = NULL;
    
    printf("%s\n", __func__);

    seg_pos = (int*)calloc(sizeof(int), partition_size);

    // calculate the sum of whole list
    for(int i = 0; i < size; i++)
    {
        list_sum += list[i];
    }

    // check if it is divisible by three
    if(list_sum % partition_size == 0)
    {
        seg_sum = list_sum / partition_size;
        // first segment always starts at zero
        seg_pos[seg_count] = 0;
        seg_count++;
        while(seg_count < partition_size)
        {
            int pre_seg_pos = seg_pos[seg_count -1];
            if(find_next_segment(seg_sum, &list[pre_seg_pos], (size -pre_seg_pos), &seg_pos[seg_count]))
            {
                seg_pos[seg_count] += seg_pos[seg_count -1];
                seg_count++;
            }
            else
            {
                break;
            }
        }

        if(seg_count == partition_size)
        {
            // print the segments
            for(int i = 0; i < seg_count -1; i++)
            {
                printf("segment %d: ", (i + 1));
                print_list(&list[seg_pos[i]], (seg_pos[i + 1] - seg_pos[i]));
            }

            // print the last segment
            printf("segment %d: ", seg_count);
            print_list(&list[seg_pos[seg_count -1]], (size - seg_pos[seg_count -1]));
        }
    }

    printf("list cannot be partitioned into 3 equal sum parts !\n");
    free(seg_pos);
}

int main ()
{
    // int list [] = {7, 6, 1, 7};
    int list [] = {1, 3, 6, 2, 7, 1, 2, 8};
    // int list [] = {7, 6, 2, 7};
    // int list [] = {0, 0, 0};
    // int list [] = {0, 0, 0, 0};
    // int list [] = {0, 0, 0, 1};
    // int list [] = {0, 0, 0, 3};
    int size = (sizeof(list) / sizeof(int));
    partition_to_three_equal_parts(list, size);
    partition_to_equal_parts(3, list, size);
    return 0;
}