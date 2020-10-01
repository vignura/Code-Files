#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <execinfo.h>
#include <setjmp.h>

#define SIZE		100
#define true		1
#define false		0

jmp_buf g_jbuf;	
int g_isPtrCheck = false;

void sigsegv_handler(int signo);

int isValidPointer(char *ptr)
{
	char ch = 0;
	g_isPtrCheck = true;

	/* pass 1 or no zero values sigsetjmp 
	to save signal masks or */
	if(!sigsetjmp(g_jbuf, 1))
	{
		ch = *ptr;
		g_isPtrCheck = false;
		return true;
	}

	g_isPtrCheck = false;
	return false;
}

void sigsegv_handler(int signo)
{
	void *array[SIZE];
	int iRetVal;

	/* if segfault is created during pointer 
	 validation, ie intentionaly, then long jump */
	// printf("Segfault: %d\n", g_isPtrCheck);
	if(g_isPtrCheck == true)
	{
		siglongjmp(g_jbuf, 1);
	}
	/* else print back trace and abort */
	else
	{
		printf("\nSegfault: %d\n", signo);
		printf("Stack Trace:\n");
		iRetVal = backtrace(array, SIZE);
		backtrace_symbols_fd(array, iRetVal, STDERR_FILENO);
		abort();
	}
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
	int a = 0;
	/* initialize a segfault handler */
	signal(SIGSEGV, sigsegv_handler);

	// create_segfault();
	if(isValidPointer((char *)&a))
	// if(isValidPointer((char *)a))
	{
		printf("Valid Pointer\n");
	}
	else
	{
		printf("Invalid Pointer\n");
	}

	if(isValidPointer((char *)a))
	{
		printf("Valid Pointer\n");
	}
	else
	{
		printf("Invalid Pointer\n");
	}
	
	create_segfault();

	return 0;
}
