#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <execinfo.h>

#define SIZE		100

void sigsegv_handler(int signo)
{
	void *array[SIZE];
	int iRetVal;

	printf("\nSegfault: %d\n", signo);
	printf("Stack Trace:\n");
	iRetVal = backtrace(array, SIZE);
	// printf("backtrace returned: %d\n", iRetVal);
	// backtrace_symbols_fd(array, SIZE, STDERR_FILENO);
	backtrace_symbols_fd(array, iRetVal, STDERR_FILENO);
	abort();
}

void create_segfault()
{
	int a = 0xAA;

	/* accessing a null pointer to cause segfault */
	*((int *)0xBB) = 1;
	
	return;
}

int main(int argc, char const *argv[])
{
	/* initialize a segfault handler */
	signal(SIGSEGV, sigsegv_handler);

	create_segfault();

	return 0;
}

