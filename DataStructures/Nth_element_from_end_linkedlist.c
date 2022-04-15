#include <stdio.h>
#include <stdbool.h>

#include "linkedlist.h"
#define LIST_SIZE		10

void nth_element_from_last_1(node *head, int n)
{
	int list_size = 0;
	node* list = head;
	
	printf ("%s: finding %d element from last of the list... ", __func__, n);
	while (list != NULL)
	{
		list_size++;
		list = list->next;
	}

	if (n <= list_size && n > 0)
	{
		list = head;
		for (int i = 0; i < list_size -n; ++i)
		{
			list = list->next;
		}
		printf ("%d\n", list->data);
	}
	else
	{
		printf ("not in list\n");
	}
}

void nth_element_from_last_2(node *head, int n)
{
	int list_size = 0;
	node* list = head;
	node* found = head;
	bool is_found = false;


	printf ("%s: finding %d element from last of the list... ", __func__, n);
	if (n > 0)
	{
		while (list != NULL)
		{
			list_size++;
			if (list_size > n)
			{
				found = found->next;
				is_found = true;
			}
			list = list->next;
		}
	}

	if (is_found)
	{
		printf ("%d\n", found->data);
	}
	else
	{
		printf ("not in list\n");
	}
}

int main(int argc, char const *argv[])
{
	node* numlist = NULL;
	int find = 4;
	create_list(&numlist, LIST_SIZE);
	print_list(numlist);
	nth_element_from_last_1(numlist, find);
	nth_element_from_last_2(numlist, find);

	return 0;
}