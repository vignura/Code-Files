#include <stdio.h>

void quick_swap(int *a, int *b)
{
	if (a != NULL && b != NULL)
	{
		// here adding refers to xoring
		// adding 'b' to 'a', so now 'a' has both 'a' and 'b' in it
		(*a) ^= (*b);
		// adding 'a + b' to 'b', so now 'b' has 'a'  
		(*b) ^= (*a);
		// adding 'b' which now has 'a' to 'a + b', gives 'b'
		(*a) ^= (*b);
	}
}

int main(int argc, char const *argv[])
{
	int a = -1;
	int b = 10;

	printf("before swap\na = %d b = %d\n", a, b);
	quick_swap(&a, &b);
	printf("after swap\na = %d b = %d\n", a, b);
	return 0;
}