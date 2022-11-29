#include <stdio.h>

/**
 * Number Binary-Repr  XOR-from-1-to-n
	1         1           [0001]
	2        10           [0011]
	3        11           [0000]  <----- We get a 0
	4       100           [0100]  <----- Equals to n
	5       101           [0001]
	6       110           [0111]
	7       111           [0000]  <----- We get 0
	8      1000           [1000]  <----- Equals to n
	9      1001           [0001]
	10     1010           [1011]
	11     1011           [0000] <------ We get 0
	12     1100           [1100] <------ Equals to n
**/
unsigned int xor_one_to_n(unsigned int n)
{
	unsigned int res = 0;

	if (n % 4 == 0)
		res = n;
	else if (n % 4 == 1)
		res = 1;
	else if (n % 4 == 2)
		res = n + 1;
	else // n % 4 == 3
		res = 0;

	return res;
}	

int main(int argc, char const *argv[])
{
	unsigned int n = 7;
	unsigned int res = xor_one_to_n(n);
	printf("xor of 1 to %d is %d[0x%x]\n", n, res, res);
	return 0;
}