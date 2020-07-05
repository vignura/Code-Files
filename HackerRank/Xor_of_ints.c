#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE		10

int cmp(const void *a, const void *b)
{
	return (*(int *)a - *(int *)b);
}

int main(int argc, char const *argv[])
{
	unsigned int key[] = {0x12345678, 0xABCDEF12, 0xFEDCBA21};
	unsigned int Xor[SIZE] = {0};

	srand(time(NULL));

	for(int i = 0; i < SIZE; i++)
	{
		// Xor[i] = ((i ^ key[0]) ^ key[1]) ^ key[2];
		// Xor[i] = (i ^ key[0]) % (SIZE * 2);
		Xor[i] = ((((rand() ^ key[0]) ^ key[1]) ^ key[2]) ^ key[0]) % (SIZE * 2);
		// printf("0x%08X ^ key: 0x%08X [%d] \n", i, Xor[i], (Xor[i] % SIZE));
	}

	/* sort the array */
	qsort(Xor, SIZE, sizeof(int), cmp);

	/* find any repitation */
	for(int i = 0; i < SIZE -1; i++)
	{
		if(Xor[i] == Xor[i + 1])
		{
			printf("Repitation at %d: %d\n", i, Xor[i]);
			break;
		}
	}

	// printf("[ ");
	// for(int i = 0; i < SIZE; i++)
	// {
	// 	printf("%d ", Xor[i]);
	// }
	// printf("]\n");

	return 0;
}