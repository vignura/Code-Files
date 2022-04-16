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
		// move to next node
		list = list->next;
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
	}

	return has_loop;
}

void remove_loop(node* head)
{
	node* list = head;
	node* jump = head;
	node* loop_tail = NULL;
	bool has_loop = false;

	while (list != NULL && jump != NULL)
	{	
		// used for tracking the last node in loop
		loop_tail = list;	
		// move to next node
		list = list->next;
		// jump 2 nodes
		jump = jump->next;
		if (jump != NULL)
		{
			jump = jump->next;
		}

		if (list == jump)
		{
			has_loop = true;
			// printf("pointer meet at %p: %d\n", list, list->data);
			break;
		}
		else
		{
			// printf("[%d, %d]\n", list->data, jump->data);
		}
	}

	// if list == head, it indicates that the list
	// is circular linked list
	if(has_loop && list != head)
	{
		// printf("trying to remove loop\n");
		list = head;
		loop_tail = NULL;
		while (list != jump)
		{
			loop_tail = jump;
			jump = jump->next;
			list = list->next;
		}
		loop_tail->next = NULL;
	}
	else
	{
		loop_tail->next = NULL;
	}
}

int main(int argc, char const *argv[])
{
	node* list1 = NULL;
	node* list2	= NULL;
	node* list3 = NULL;
	node* list4 = NULL;

	create_list (&list1, LIST_SIZE);
	create_list (&list2, LIST_SIZE);
	list3 = clone_list(list1);
	list4 = clone_list(list2); 

	print_list(list1);
	print_list(list2);
	
	// make list2 and list4 cyclic
	make_list_cyclic(list2);
	make_list_cyclic(list4);

	list3 = concadinate_lists(list3, list4);
	print_list_bounded(list3, LIST_SIZE *2);

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
		printf("removing loop... ");
		remove_loop(list2);
		print_list(list2);
	}
	else
	{
		printf("no\n");
	}

	printf("checking if list %p has loop... ", list3);
	if (list_has_loop(list3))
	{
		printf("yes\n");
		printf("removing loop... ");
		remove_loop(list3);
		print_list(list3);
	}
	else
	{
		printf("no\n");
	}

	free_list(list1);
	free_list(list2);
	free_list(list3);
	// list 4 is part of list 3 now so
	// it is enough to free list 3
	return 0;
}