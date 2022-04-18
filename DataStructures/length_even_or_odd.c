#include <stdio.h>
#include <stdbool.h>

#include "linkedlist.h"
#define LIST_SIZE 1

bool is_length_even(node* head)
{
	bool is_even = true;
	node* jump = head;

	while (jump != NULL)
	{
		// do a double jump
		if (jump->next != NULL)
		{
			jump = jump->next->next;
		}
		else
		{
			break;
		}
	}

	if (jump != NULL)
	{
		is_even = false;
	}

	return is_even;
}

int main(int argc, char const *argv[])
{
	node* list = NULL;

	create_list(&list, LIST_SIZE);
	print_list(list);
	if (is_length_even(list))
	{
		printf ("list length is even\n");
	}
	else
	{
		printf ("list length is odd\n");
	}

	return 0;
}