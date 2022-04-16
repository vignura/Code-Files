#include <stdio.h>
#include <stdbool.h>

#include "linkedlist.h"
#define LIST_SIZE 10

/* this function creates makes the two list intersect. The
   intersection point on list 1 is m nodes away form list1
   and n nodes away from list2. The nodes in list2 after m
   nodes are freed. Make sure m and n are lesser than the
   corresponding list sizes */
void create_intersection (node* head_1, node* head_2, int m, int n)
{
	int count = 0;
	node* node_m = head_1;
	node* node_n = head_2;
	node* temp = NULL;

	// move to node m in list 1
	while (node_m != NULL)
	{
		count++;
		if (count == m)
			break;
		else
			node_m = node_m->next;
	}

	// move to node n in list 2
	count = 0;
	while (node_n != NULL)
	{
		count++;
		if (count == n)
			break;
		else
			node_n = node_n->next;
	}

	if (node_m != NULL && node_n != NULL)
	{
		// discard the leftover nodes in list2
		temp = node_n->next;
		free_list(temp);

		// create intersection, make the nth node
		// on list 2 to point to mth node on list 1
		node_n->next = node_m;
	}
	else
	{
		printf ("invalid m and n values for creating intersection\n");
	}
}

node* find_intersection(node* head_1, node* head_2)
{
	// assuming list 1 is longer
	node* list1 = head_1;
	node* list2 = head_2;
	node* short_list = NULL;
	int len1 = 0;
	int len2 = 0;
	int diff = 0;
	
	// find the length of both lists
	while (list1 != NULL && list2 != NULL)
	{
		len1++;
		len2++;
		list1 = list1->next;
		list2 = list2->next;
	}

	// find the remaining length of the bigger list
	if (list1 != NULL)
	{
		while (list1 != NULL)
		{
			len1++;
			list1 = list1->next;
		}
	}
	else
	{
		while (list2 != NULL)
		{
			len2++;
			list2 = list2->next;
		}
	}

	printf("list1 length: %d list2 length: %d\n", len1, len2);

	// check if list2 is the longer list1
	if (len2 > len1)
	{
		list1 = head_2;
		list2 = head_1;
		diff = len2 - len1;
	}
	else
	{
		list1 = head_1;
		list2 = head_2;
		diff = len1 - len2;
	}

	// move for diff len list1 (longer list)
	while (diff > 0 && list1 != NULL)
	{
		list1 = list1->next;
		diff--;
	}

	while (list1 != NULL && list2 != NULL)
	{
		if (list1 == list2)
		{
			break;
		}
		list1 = list1->next;
		list2 = list2->next;
	}

	return list1;
}

node* remove_intersection(node* head, node* intersection)
{
	node* list = head;
	node* prev = NULL;
	while (list != NULL && list != intersection)
	{
		prev = list;
		list = list->next;
	}
	prev->next = NULL;
	return head;
}

int main(int argc, char const *argv[])
{
	node* list1 = NULL;
	node* list2 = NULL;

	create_list(&list1, LIST_SIZE);
	create_list(&list2, LIST_SIZE);

	printf("Lists before intersection:\n");
	print_list(list1);
	print_list(list2);

	create_intersection(list1, list2, 8, 2);
	printf("Lists after intersection:\n");
	print_list(list1);
	print_list(list2);

	node* intersection = find_intersection(list1, list2);
	printf("intersection point is at %p : %d\n", intersection, intersection->data);

	list1 = remove_intersection(list1, intersection);
	free_list(list1);
	free_list(list2);

	return 0;
}