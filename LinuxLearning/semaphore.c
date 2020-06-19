#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>
#include <fcntl.h> /* Defines O_* constants */
#include <sys/stat.h> /* Defines mode constants */
#include <signal.h>
#include <stdlib.h>
#include <execinfo.h>

#define MAX_THREADS					2
#define THREAD_RUN_CNT				50
#define SEM_NAME					"sem_test"
#define BACKTRACE_SIZE				100

int ThreadFun(void * arg);
int createThreads();
int joinThreads();

int g_iThreadState[MAX_THREADS] = {0};
pthread_t g_ThreadID[MAX_THREADS] = {0};
sem_t *g_sem = 0;

void sigsegv_handler(int signo)
{
	void *array[BACKTRACE_SIZE];
	int iRetVal;

	printf("\nSegfault: %d\n", signo);
	printf("Stack Trace:\n");
	iRetVal = backtrace(array, BACKTRACE_SIZE);
	// printf("backtrace returned: %d\n", iRetVal);
	// backtrace_symbols_fd(array, BACKTRACE_SIZE, STDERR_FILENO);
	backtrace_symbols_fd(array, iRetVal, STDERR_FILENO);
	abort();
}

int main(int argc, char const *argv[])
{
	int iRet = 0;

	/* initialize a segfault handler */
	signal(SIGSEGV, sigsegv_handler);

	/* create a sempahore */
	g_sem = sem_open(SEM_NAME, O_CREAT | O_EXCL, 0, 0);
	if(g_sem == NULL)
	{
		printf("ERRPR: sem_open\n");
		//return -1;
	}
	else
	{
		iRet = createThreads();
		if(iRet != 0)
		{
			printf("ERROR: createThreads\n");
		}

		iRet = joinThreads();
		if(iRet != 0)
		{
			printf("ERROR: joinThreads\n");
		}
	}

	/* close the sempahore */
	iRet = sem_close(g_sem);
	if(iRet != 0)
	{
		perror("sem_close");
	}

	/* unlink the sempahore */
	iRet = sem_unlink(SEM_NAME);
	if(iRet != 0)
	{
		perror("sem_unlink");
	}

	return 0;
}

int joinThreads()
{
	int iRet = 0;
	int i = 0;

	for (i = 0; i < MAX_THREADS; ++i)
	{
		iRet = pthread_join(g_ThreadID[i], NULL);
		if(iRet != 0)
		{
			printf("ERROR: pthread_join for thread ID: %d\n", i);
			break;
		}
		else
		{
			printf("Joined Thread %d with ID: %d\n", i, g_ThreadID[i]);
		}
	}

	return iRet;
}

int createThreads()
{
	int iRet = 0;
	int i = 0;

	for (i = 0; i < MAX_THREADS; ++i)
	{
		g_iThreadState[i] = 1;

		iRet = pthread_create(&g_ThreadID[i], NULL, ThreadFun, &i);
		if(iRet != 0)
		{
			printf("ERROR: pthread_create for thread ID: %d\n", i);
			break;
		}
		else
		{
			printf("Created Thread %d with ID: %d\n", i, g_ThreadID[i]);
		}

		sleep(1);
	}

	return iRet;
}

int ThreadFun(void * arg)
{
	int iCount = 0;
	struct timespec t_req = {0};
	struct timespec t_rem = {0};

	if(arg == NULL)
	{
		return -1;
	}

	int ThreadID = *(int *)arg;

	while(g_iThreadState[ThreadID])
	{
		if(ThreadID % 2 == 0)
		{
			sem_wait(g_sem);
		}
		else
		{
			/* sleep is added so that single thread does */
			t_req.tv_sec = 0;
			t_req.tv_nsec = (2 * 1000 * 1000);
			nanosleep(&t_req, &t_rem);
		}

		printf("[ID: %d] count: %d\n", ThreadID, iCount);

		if(ThreadID % 2 == 1)
		{
			sem_post(g_sem);
		}
		

		if(iCount == THREAD_RUN_CNT)
		{
			g_iThreadState[ThreadID] = 0;
			// printf("[ID: %d] exiting\n", ThreadID);
		}

		iCount++;
	}

	return 0;
}