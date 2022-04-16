#include <stdio.h>
#include <stdlib.h>

#include "linkedlist.h"

void print_list(node* head)
{
	node* list = head;
	printf("[");
	while(list != NULL)
	{
		printf ("%d ", list->data);
		list = list->next;
	}
	printf("\b]\n");
}

void print_list_bounded(node* head, int bound)
{
	node* list = head;
	int count  = 0;
	printf("[");
	while(list != NULL && count < bound)
	{
		printf ("%d ", list->data);
		list = list->next;
		count++;
	}
	printf("\b]\n");
}

void create_list(node** head, int size)
{
	static int data = 0;
	node* new_node = NULL;

	(*head) = (node*)calloc(1, sizeof(node));
		
	for (int i = 0; i < size; i++, data++)
	{
		if (i == 0)
		{
			(*head)->data = data +1;
			(*head)->next = (node*)calloc(1, sizeof(node));
			new_node = (*head)->next;
		}
		else if (i > 0 && i < (size -1))
		{
			new_node->data = data +1;
			new_node->next = (node*)calloc(1, sizeof(node));
			new_node = new_node->next;
		}
		else // last node
		{
			new_node->data = data +1;
			new_node->next = NULL;
		}

	} 
}

void free_list(node* head)
{
	node* list = head;
	node* prev = head;

	while (list != NULL)
	{
		prev = list;
		list = list->next;
		free(prev);
	}
}

node* clone_list(node* head)
{
	node* list = head;
	node* clone = NULL;
	node* clone_head = NULL;

	while (list != NULL)
	{
		if (clone_head == NULL)
		{
			clone_head = (node*) calloc(1, sizeof(node));
			clone = clone_head;
		}

		clone->data = list->data;

		if (list->next != NULL)
		{
			clone->next = (node*) calloc(1, sizeof(node));
		}
		else
		{
			clone->next = NULL;
		}

		clone = clone->next;
		list = list->next;
	}

	return clone_head;
}

node* concadinate_lists(node* head_1, node* head_2)
{
	if (head_1 != NULL && head_2 != NULL)
	{
		node* list1 = head_1;
		// traverse to last node
		while (list1 != NULL && list1->next != NULL)
		{
			list1 = list1->next;
		}
		list1->next = head_2;
	}

	return head_1;
}