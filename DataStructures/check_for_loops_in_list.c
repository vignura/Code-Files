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

bool list_has_loop(node* head)
{
	bool has_loop = false;
	node* list = head;
	node* jump = head;

	while (list != NULL && jump != NULL)
	{
		// jump 2 nodes
		jump = jump->next;
		if (jump != NULL)
		{
			jump = jump->next;
		}

		if (list == jump)
		{
			has_loop = true;
			break;
		}

		// move to next node
		list = list->next;
	}

	return has_loop;
}

int main(int argc, char const *argv[])
{
	node* list1 = NULL;
	node* list2	= NULL;
	node* list3 = NULL;

	create_list (&list1, LIST_SIZE);
	create_list (&list2, LIST_SIZE);
	list3 = clone_list(list1); 

	print_list(list1);
	print_list(list2);
	// make list2 cyclic
	make_list_cyclic(list2);
	list3 = concadinate_lists(list3, list2);
	print_list_bounded(list3, LIST_SIZE *5);

	printf("checking if list %p has loop... ", list1);
	if (list_has_loop(list1))
	{
		printf("yes\n");
	}
	else
	{
		printf("no\n");
	}

	printf("checking if list %p has loop... ", list2);
	if (list_has_loop(list2))
	{
		printf("yes\n");
	}
	else
	{
		printf("no\n");
	}

	printf("checking if list %p has loop... ", list3);
	if (list_has_loop(list3))
	{
		printf("yes\n");
	}
	else
	{
		printf("no\n");
	}

	return 0;
}