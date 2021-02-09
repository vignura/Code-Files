#include <stdio.h>

void print_array(int* array, int size)
{
 	if(size < 1)
	{
		return;
	}

	// pass the array in reverse as the 
	// stack is emptied in reverse which the basis of
	// recursion
	printf("%d, ", array[0]);
	print_array(array + 1, (size -1));
}

void print_array_reverse(int* array, int size)
{
	// printf("size: %d\n", size);
 	if(size < 1)
	{
		return;
	}

	// pass the array in reverse as the 
	// stack is emptied in reverse which the basis of
	// recursion
	print_array_reverse(array + 1, (size -1));
	printf("%d, ", array[0]);
}

void print_array_reverse_1(int* array, int size)
{
	if(size > 0)
	{
		printf("%d, ", array[size -1]);
	}
	else
	{
		return;
	}
	
	print_array_reverse_1(array, size -1);	
}

int main(int argc, char const *argv[])
{
	int a = 0;
	int b = 0;
	int array[] = {1, 2, 3, 4, 5};
	// int array[] = {1, 2};
	// int array[] = {1};
	
	printf("print array\n");
	print_array(array, (sizeof(array) / sizeof(int)));
	printf("\n");
	print_array_reverse(array, (sizeof(array) / sizeof(int)));
	printf("\n");
	print_array_reverse_1(array, (sizeof(array) / sizeof(int)));
	printf("\n");
	
	return 0;
}