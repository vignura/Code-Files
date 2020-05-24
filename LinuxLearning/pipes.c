#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define READ_PIPE			0
#define WRITE_PIPE			1

void ChildTask(int* pipefd, int iBlockSize, int iBlockCount);
void ParentTask(int* pipefd, int iBlockSize, int iBlockCount);
void printAgs(int argc, char const *argv[]);

char g_arrcReadBuff[1024 * 1024] = {0};
char g_arrcWriteBuff[1024 * 1024] = {0};

int main(int argc, char const *argv[])
{
	int iRetVal = 0;
	int iBlockSize = 0;
	int iBlockCount = 0;

	int pipefd[2] = {0};
	pid_t ChildPid = 0;

	if(argc  < 3)
	{
		printf("usage: %s [block size] [block count]\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	else
	{
		/*printAgs(argc, argv);*/
	}

	iRetVal = sscanf(argv[1], "%d", &iBlockSize);
	if(iRetVal != 1)
	{
		printf("Invalid block size: %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	iRetVal = sscanf(argv[2], "%d", &iBlockCount);
	if(iRetVal != 1)
	{
		printf("Invalid block count: %s\n", argv[2]);
		exit(EXIT_FAILURE);
	}

	printf("block size: %d\tblock count: %d\n", iBlockSize, iBlockCount);

	/* create a pipe */
	if(pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	/* fork a child process */
	ChildPid = fork();
	if(ChildPid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}

	/* child process has pid = 0 */
	if(ChildPid == 0)
	{
		ChildTask(pipefd, iBlockSize, iBlockCount);
	}
	else
	{
		ParentTask(pipefd, iBlockSize, iBlockCount);
	}

	return 0;
}

void ChildTask(int* pipefd, int iBlockSize, int iBlockCount)
{
	int iIndex = 0;
	int iReadBytes = 0;

	printf("Child Task\n");

	/* close unused write end */
	close(pipefd[WRITE_PIPE]);

	for(iIndex = 0; iIndex < iBlockCount; iIndex++)
	{
		iReadBytes = read(pipefd[READ_PIPE], g_arrcReadBuff, iBlockSize);
		// printf("read: %d bytes\n", iReadBytes);
	}

	/* close read end */
	close(pipefd[READ_PIPE]);
}

void ParentTask(int* pipefd, int iBlockSize, int iBlockCount)
{
	int iIndex = 0;

	printf("Parent Task\n");

	/* close unused read end */
	close(pipefd[READ_PIPE]);

	for(iIndex = 0; iIndex < iBlockCount; iIndex++)
	{
		write(pipefd[WRITE_PIPE], g_arrcWriteBuff, iBlockSize);
		// printf("wrote: %d bytes\n", iBlockSize);
	}

	/* close write end */
	close(pipefd[WRITE_PIPE]);
}

void printAgs(int argc, char const *argv[])
{
	int iIndex = 0;

	for (iIndex; iIndex < argc; iIndex++)
	{
		printf("%d. %s\n", (iIndex + 1), argv[iIndex]);
	}
}