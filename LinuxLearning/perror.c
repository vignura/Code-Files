#include <stdio.h>
/* used for open call */
#include <fcntl.h>

int main()
{
	int fd = 0;

	printf("Testing perror()\n");
	
	/* open an non exisxting file */
	fd = open("NoExistingFile.txt", O_APPEND);
	if(fd = -1)
	{
		perror("open");
	}

	return 0;
}