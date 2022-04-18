#include <stdio.h>
#include <stdbool.h>

#include "linkedlist.h"
#define LIST_SIZE 11

node* find_middle_node(node* head)
{
	node* list = head;
	node* middle_node = head;

	while (list != NULL && middle_node!= NULL)
	{
		// move list by two steps
		list = list->next;
		if(list != NULL)
		{
			list = list->next;
			// move middle node by one step
			middle_node = middle_node->next;		
		}
	}

	return middle_node;
}

int main(int argc, char const *argv[])
{
	node* list = NULL;
	node* middle_node = NULL;

	create_list(&list, LIST_SIZE);
	print_list(list);
	middle_node = find_middle_node(list);
	printf("middle node: %p : %d\n", middle_node, middle_node->data);
	
	return 0;
}