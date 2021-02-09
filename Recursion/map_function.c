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

void map(int* array, int size, int(*fun)(int))
{
	if(size < 1)
	{
		return;
	}

	printf("%d, ", (*fun)(array[0]));	
	map(array + 1, (size -1), fun);
}

void test_fun_ptr(int(*fun)(int))
{
	printf("%d\n", (*fun)(1));
}

int add_one(int num)
{
	return num + 1;
}

int square(int num)
{
	return num * num;
}

int scale_by_2(int num)
{
	return num * 2;
}

int main(int argc, char const *argv[])
{
	int a = 0;
	int b = 0;
	int array[] = {1, 2, 3, 4, 5};
	
	printf("testing funciton pointer\n");	
	test_fun_ptr(add_one);
	printf("map function\n");
	print_array(array, (sizeof(array) / sizeof(int)));
	printf("\n");
	printf("mapping with add_one ...\n");
	map(array, (sizeof(array) / sizeof(int)), add_one);
	printf("\n");
	printf("mapping with square ...\n");
	map(array, (sizeof(array) / sizeof(int)), square);
	printf("\n");
	printf("mapping with scale_by_2 ...\n");
	map(array, (sizeof(array) / sizeof(int)), scale_by_2);
	printf("\n");
	
	return 0;
}