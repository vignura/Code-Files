#include <stdio.h>
#include <stdlib.h>

#define MEM_SIZE (128 - 10)

int main()
{
	char *pc = NULL;
	int *pi = NULL;
	int idiff = 0;
	int iSum = 0;

	/* allocate some memory */
	pc = (char *)malloc(sizeof(char) * MEM_SIZE);
	if(pc == NULL)
	{
		printf("malloc failed\n");
	}
	else
	{
		pi = pc - sizeof(long long);
		printf("allocated: %d[0x%X] bytes\n", MEM_SIZE, MEM_SIZE);
		printf("pc: 0x%X\tpi: 0x%X\n", pc, pi);
		printf("allocated memory: %d[0x%X] bytes\n", (*pi), (*pi));

		idiff = ((*pi) - MEM_SIZE);
		printf("Difference: %d[0x%X]\n", idiff, idiff);
		free(pc);
	}

	return 0;
}