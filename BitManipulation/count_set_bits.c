#include <stdio.h>

unsigned int count_set_bits(unsigned int num)
{
	unsigned int count = 0;
	/**
	 * Brian Kernighan’s Algorithm
	 * When we subtract one form any number, it filps
	 * all bits form the right most set bit, so doing
	 * this in loop till the number becomes zero will 
	 * give the number of set bits. Time complexity is
	 * **/
	while (num)
	{
		num &= (num -1);
		count++;
	} 

	return count;
}

int main(int argc, char const *argv[])
{
	unsigned int num = 0b1000;
	printf ("There are %d set bits in %d\n", count_set_bits(num), num);
	return 0;
}