#include <stdio.h>

typedef struct node{

	int num;
	node *next;
}node;

void buildList(node **head, int size);
void printList(node *head);
void reverseList(node **head);

int main()
{
    node *head = NULL;
    buildList(&head, 10);
    printList(head);
    reverseList(&head);
    printList(head);
	return 0;
}

void buildList(node **head, int size)
{
    int i = 0;
	node* n = NULL;
	*head = new node;
	n = *head;
	
	for(i = 0; i < (size -1); i++){
		n->num = i;
		n->next = new node;
		n = n->next;
	}
	n->num = i;
	n->next = NULL;
}

void printList(node *head)
{
	node  *n = head;
	
	printf("[ ");
	while(n != NULL){

		printf("%d ", n->num);
		n = n->next;
	}	
	printf("]\n");
}

void reverseList(node **head)
{
    node *n = *head;
    node *n1 = *head;
    node *n2 = *head;
    
    while(n != NULL)
    {
        n2 = n1;
        n1 = n;
        n = n->next;
        n1->next = n2;
        // printf("%x \t%x \t%x \t%x\n", n2, n1, n, n1->next);
    }
    (*head)->next = NULL;
    // printList(n1);
    *head = n1;
}
