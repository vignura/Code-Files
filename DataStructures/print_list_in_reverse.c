#include <stdio.h>
#include <stdbool.h>

#include "linkedlist.h"
#define LIST_SIZE 11

void print_list_reverse(node* list)
{
	static int count;

	if (list != NULL)
	{
		count++;
		print_list_reverse(list->next);
		count--;
		printf ("%d ", list->data);
		if(count == 0)
		{
			printf ("\b]\n");
		}
		else
		{
			// printf ("count: %d\n", count);
		}
	}
	else
	{
		printf ("[");
	}
}

int main(int argc, char const *argv[])
{
	node* list = NULL;
	create_list(&list, LIST_SIZE);
	print_list(list);
	print_list_reverse(list);
	return 0;
}