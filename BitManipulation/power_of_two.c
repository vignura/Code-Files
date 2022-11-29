#include <stdio.h>
#include <stdbool.h>

bool is_power_of_two(unsigned int num)
{
	/**
	 * Number that are powers of two will have only 
	 * one bit set. So when we subtract 1 from the number
	 * then all the unset bits before the set bit becomes
	 * set and the set bit becomes zero. So anding them both
	 * will result in zero. 
	 * 8 - 1000; (8-1)=7 - 0111; (8 & 7)
	 * 1000 & 0111 = 0 **/

	// the below expression does not handle the case, when
	// number is zero, so logical and the result with number again
	// return !(num & (num -1));

	return num && (!(num & (num -1))); 
}

int main(int argc, char const *argv[])
{
	unsigned int num = 1024;

	if (is_power_of_two(num))
	{
		printf("%d is a power of two\n", num);
	}
	else
	{
		printf("%d is not a power of two\n", num);	
	}

	return 0;
}