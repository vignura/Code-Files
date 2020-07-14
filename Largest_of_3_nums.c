#include <stdio.h>
#include <string.h>

#define MAX_NUMS		3

int main(int argc, char const *argv[])
{
	int iIndex = 0;
	int iRetVal = 0;
	int iNum[MAX_NUMS] = {0};
	int iLargestNum = 0;

	if(argc != 4)
	{
		printf("usage: %s [num1] [num2] [num3]\n", argv[0]);
		return 0;
	}

	/* scan arguments from command line */
	/* iIndex+1 is used to skip the first arg which the name of the executable */
	for (iIndex = 0; iIndex < MAX_NUMS; iIndex++)
	{
		iRetVal = sscanf(argv[iIndex + 1], "%d", &iNum[iIndex]);
		if(iRetVal != 1)
		{
			printf("ERROR: sscanf\n");
		}
	}

	/* find the largest number */
	/* set the iLargestNum to first arg, so that
		we don't return zero as largest value if all
		theree numbers are negative */
	iLargestNum = iNum[0];
	/* starting loop index at 1 as we have already assigned 
		iLargestNum to first argument */
	for (iIndex = 1; iIndex < MAX_NUMS; iIndex++)
	{
		if(iLargestNum < iNum[iIndex])
		{
			iLargestNum = iNum[iIndex];
		}
	}

	printf("Largest Number: %d\n", iLargestNum);

	return 0;
}
