#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

static void sig_handler(int sig)
{
	printf("PID:%ld caught signal %d (%s)\n", getpid(), sig, strsignal(sig));
	abort();
}

int main(int argc, char const *argv[])
{
	char arrcBuff[10] = {0};
	char arrcBuff_1[10] = {0};

	/* register signal handler */
	signal(SIGSEGV, sig_handler);

	printf("Creating Segfault...\n");
	arrcBuff[10000] = 1;
	return 0;
}