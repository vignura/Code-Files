#ifndef __LINKEDLIST_H_
#define __LINKEDLIST_H_

typedef struct node node;
struct node {
	int data;
	node* next;
};

void print_list(node* head);
void print_list_bounded(node* head, int bound);
void create_list(node** head, int size);
node* clone_list(node* head);
node* concadinate_lists(node* head_1, node* head_2);
void free_list(node* head);

#endif // __LINKEDLIST_H_