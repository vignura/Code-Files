#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	// char *a[4] = {"sridhar","raghava","shashi","srikanth"};
	// char *a[4] = {"1","22","333","4444"};
	char *a[3] = {"1","22","333"};
	printf("size of a : %d\n", sizeof(a));
	printf("size of char * : %d\n", sizeof(char *));
	printf("size: %d\n", (sizeof(a) / sizeof(char *)));
	printf("size of a[0]: %d\n", (sizeof(a) / sizeof(a[0])));
	printf("strlen of a[0] : %d\n", strlen(a[0]));

	return 0;
}
