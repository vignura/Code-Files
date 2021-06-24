/* compile command: gcc detached_threads.c -o detached_threads -lpthread*/
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SLEEP_TIME_SEC	5
#define STRING "allocated memory to a pointer inside detached thread!!"
char* string;

void* thread_func(void* arg)
{
	string = (char*)malloc(sizeof(STRING));
	strncpy(string, STRING, sizeof(STRING));
	printf("Thread: %s\n", string);

	return NULL;
}

int main(int argc, char const *argv[])
{
	int iRet = 0;
	pthread_t ThreadID;

	printf("creating a detached thread...\n");
	iRet = pthread_create(&ThreadID, NULL, thread_func, NULL);
	if(iRet != 0)
	{
		printf("ERROR: pthread_create falied");
		return -1;
	}

	iRet = pthread_detach(ThreadID);
	if(iRet != 0)
	{
		printf("ERROR: pthread_detach falied");
		return -1;
	}

	printf("sleeping for %d seconds...\n", SLEEP_TIME_SEC);
	sleep(SLEEP_TIME_SEC);

	if(string != NULL)
	{
		printf("Main: %s\n", string);
	}

	return 0;
}