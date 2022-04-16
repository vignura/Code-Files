#include <stdio.h>
#include <stdbool.h>

#include "linkedlist.h"
#define LIST_SIZE 10

node* reverse_list(node* head)
{
	node* next_node = NULL;
	node* reverse_head = NULL;

	while (head != NULL)
	{
		next_node = head->next;
		head->next = reverse_head;
		reverse_head = head;
		head = next_node;
	}

	return reverse_head;
}

int main(int argc, char const *argv[])
{
	node* list = NULL;
	
	create_list(&list, LIST_SIZE);
	print_list(list);
	list = reverse_list(list);
	print_list(list);

	free_list(list);

	return 0;
}