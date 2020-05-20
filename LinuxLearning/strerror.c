#include <stdio.h>
/* used for open call */
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main()
{
	int fd = 0;

	printf("Testing strerror()\n");
	
	/* open an non exisxting file */
	fd = open("NoExistingFile.txt", O_APPEND);
	if(fd = -1)
	{
		printf("error: %s\n", strerror(errno));
	}

	return 0;
}