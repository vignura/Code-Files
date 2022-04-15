#include <stdio.h>
#include <stdbool.h>

#include "linkedlist.h"
#define LIST_SIZE 10

void make_list_cyclic(node* head)
{
	node* list = head;
	
	// traverse to the last node
	while (list != NULL && list->next != NULL)
	{
		list = list->next;
	}

	if (list != NULL)
	{
		list->next = head;
	}
	
}

bool is_list_cyclic(node* head)
{
	bool is_cyclic = false;
	node* list = head;

	while (list != NULL)
	{
		list = list->next;
		if (list == head)
		{
			is_cyclic = true;
			break;
		}
	}

	return is_cyclic;
}

int main(int argc, char const *argv[])
{
	node* list = NULL;
	node* cyclic_list = NULL;
	
	create_list(&list, LIST_SIZE);
	cyclic_list = clone_list(list);

	print_list(list);
	print_list(cyclic_list);

	// make the list cyclic
	make_list_cyclic(cyclic_list);
	// print list will print indefinitely, so don't use that
	// for cyclic list, use bounded version
	// print_list(cyclic_list);
	print_list_bounded(cyclic_list, LIST_SIZE * 2);

	printf ("checking if list %p is cyclic... ", list);
	if (is_list_cyclic(list))
	{
		printf ("yes\n");
	}
	else
	{
		printf ("no\n");
	}

	printf ("checking if list %p is cyclic... ", cyclic_list);
	if (is_list_cyclic(cyclic_list))
	{
		printf ("yes\n");
	}
	else
	{
		printf ("no\n");
	}

	return 0;
}