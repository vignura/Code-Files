// A C program to demonstrate linked list based implementation of queue
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// A linked list (LL) node to store a queue entry
struct QNode {
    char *key;
    struct QNode* next;
};
 
// The queue, front stores the front node of LL and rear stores the
// last node of LL
struct Queue {
    struct QNode *front, *rear;
};

// create queueList
struct Queue *queueList = NULL;
  
// A utility function to create a new linked list node.
struct QNode* newNode(char *k)
{
    struct QNode* temp = (struct QNode*)malloc(sizeof(struct QNode));
    temp->key = malloc(10);
    strcpy(temp->key, k);
    printf("Adding to Queue req = %s\n", temp->key);
    temp->next = NULL;
    return temp;
}
  
// A utility function to create an empty queue
struct Queue* createQueue()
{
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->front = q->rear = NULL;
    return q;
}

char *getQueueValue()
{
   if (queueList == NULL || queueList->front == NULL)
   {
       return NULL;
   }

   char *retval = queueList->front->key;

   return retval;
}

// The function to add a key k to q
void enQueue(char *k)
{
    if (queueList == NULL)
    {
        queueList = createQueue();
    }
        
    // Create a new LL node
    struct QNode* temp = newNode(k);
  
    // If queue is empty, then new node is front and rear both
    if (queueList->rear == NULL) {
        queueList->front = queueList->rear = temp;
        return;
    }
  
    // Add the new node at the end of queue and change rear
    queueList->rear->next = temp;
    queueList->rear = temp;
}
  
// Function to remove a key from given queue q
void deQueue()
{
    // If queue is empty, return NULL.
    if (queueList->front == NULL)
        return;
  
    // Store previous front and move front one node ahead
    struct QNode* temp = queueList->front;
  
    queueList->front = queueList->front->next;
  
    // If front becomes NULL, then change rear also as NULL
    if (queueList->front == NULL)
        queueList->rear = NULL;
  
    printf("Completed executing task = %s\n", temp->key);
    free(temp->key);
    free(temp);
}
