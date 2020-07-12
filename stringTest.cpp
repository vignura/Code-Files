#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{

	char array[128] = {0};

	sprintf(array, "\r\n+CLIP: +919940398991");

	for(int i = 0; i < 10; i++)
	{
		printf("%c", array[i + 13]);
	}

	printf("\n");
	printf("%s\n", &array[13]);

	/* code */
	return 0;
}
