#include <bits/stdc++.h>

using namespace std;

class DoublyLinkedListNode {
    public:
        int data;
        DoublyLinkedListNode *next;
        DoublyLinkedListNode *prev;

        DoublyLinkedListNode(int node_data) {
            this->data = node_data;
            this->next = nullptr;
            this->prev = nullptr;
        }
};

class DoublyLinkedList {
    public:
        DoublyLinkedListNode *head;
        DoublyLinkedListNode *tail;

        DoublyLinkedList() {
            this->head = nullptr;
            this->tail = nullptr;
        }

        void insert_node(int node_data) {
            DoublyLinkedListNode* node = new DoublyLinkedListNode(node_data);

            if (!this->head) {
                this->head = node;
            } else {
                this->tail->next = node;
                node->prev = this->tail;
            }

            this->tail = node;
        }
};

void print_doubly_linked_list(DoublyLinkedListNode* node, string sep, ofstream& fout) {
    while (node) {
        fout << node->data;

        node = node->next;

        if (node) {
            fout << sep;
        }
    }
}

void free_doubly_linked_list(DoublyLinkedListNode* node) {
    while (node) {
        DoublyLinkedListNode* temp = node;
        node = node->next;

        free(temp);
    }
}

// Complete the sortedInsert function below.

/*
 * For your reference:
 *
 * DoublyLinkedListNode {
 *     int data;
 *     DoublyLinkedListNode* next;
 *     DoublyLinkedListNode* prev;
 * };
 *
 */
DoublyLinkedListNode* sortedInsert(DoublyLinkedListNode* head, int data) {

    DoublyLinkedListNode *node = head;
    DoublyLinkedListNode *newNode = NULL;

    if(head == NULL)
    {
        node = new DoublyLinkedListNode(data);
        node->next = NULL;
        node->prev = NULL;
        return node;
    }

    while(node != NULL)
    {   
        printf("Cmp: %d > %d\n", node->data, data);
        if(node->data > data)
        {
            printf("if 1\n");
            newNode = new DoublyLinkedListNode(data);

            if(node->prev != NULL)
            {
                newNode->next = node;
                newNode->prev = node->prev;
                node->prev->next = newNode;
                node->prev = newNode;    
            }
            else // head node
            {   
                newNode->next = node;
                newNode->prev = NULL;
                node->prev = newNode; 
                return newNode;
            }
            
            break;
        }
        
        if(node->next == NULL)
        {
            printf("if 2\n");
            node->next = new DoublyLinkedListNode(data);
            node->next->next = NULL;
            node->prev = node->next;
            break;
        }
        else
        {
            node = node->next;
        }
    }

    return head;
}

void print_list(SinglyLinkedListNode *node)
{
    printf("[ ");
    while(node != NULL)
    {
        printf("%d ");
        node = node->next;
    }
    printf("]\n");
}
int findMergeNode(SinglyLinkedListNode* head1, SinglyLinkedListNode* head2) {

    print_list(head1);
    print_list(head2);
    return 0;
}