#include <iostream>

#define BUFFER_SIZE					(1024 * 1024)
#define RECURSIVE_CALL_DEPTH		(100)

using namespace std;

void stack_overflow(int call_count)
{
	char buffer[BUFFER_SIZE] = {0};

	if(call_count < RECURSIVE_CALL_DEPTH)
	{
		printf("depth: %d\n", call_count);
		stack_overflow(call_count + 1);
	}
}

int main(int argc, char const *argv[])
{
	stack_overflow(0);
	return 0;
}