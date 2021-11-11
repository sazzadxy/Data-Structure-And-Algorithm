#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node{
    int data;
    struct Node *next;
}Node;

typedef struct {
    struct Node *head;
    struct Node *tail;
    int nodeCount;
}LinkedList;

void initList(LinkedList *);
void enqueue(LinkedList *, int);
void printQueue(LinkedList *);
int dequeue(LinkedList *);

void initList(LinkedList *listPtr)
{
    listPtr->head = NULL;
    listPtr->tail = NULL;
    listPtr->nodeCount = 0;
}

void enqueue(LinkedList *listPtr, int data)
{
    Node *newNodePtr = (Node*) malloc(sizeof(Node));

    if(newNodePtr == NULL){
        printf("Unable to allocate new node\n");
        return;
    }
    newNodePtr->data = data;
    newNodePtr->next = NULL;

    if(listPtr->nodeCount == 0){
        listPtr->head = newNodePtr;
        listPtr->tail = newNodePtr;
    }
    else{
        listPtr->tail->next = newNodePtr;
        listPtr->tail = newNodePtr;
    }
    listPtr->nodeCount++;
}

int dequeue(LinkedList *listPtr)
{
    if(listPtr->nodeCount == 0)
        return -9999;

    Node *first = listPtr->head;
    int data = first->data;

    if(listPtr->nodeCount == 1){
        listPtr->head = NULL;
        listPtr->tail = NULL;
    }

    else{
        listPtr->head = first->next;
    }
    free(first);
    listPtr->nodeCount--;
    return data;
}

void printQueue(LinkedList *listPtr)
{
    if(listPtr->nodeCount == 0){
        printf("Queue is empty\n");
        return;
    }
    Node *current = listPtr->head;
    while( current != NULL){
        printf("%4d", current->data);
        current = current->next;
    }
    printf("\n");
}

void menu()
{
    printf("    Queue using LinkedList\n");
    printf("----------------------------------------\n");
    printf("1. Insert\n");
    printf("2. Delete\n");
    printf("3. Display\n");
    printf("4. Quit\n");                   // to terminate each node
}

int main()
{
    LinkedList queue;
    initList(&queue);
    menu();
    int quit = 0;
    int data, choice;

    while(quit != 1){
        printf("Please input your choice: ");
        scanf("%d", &choice);
        switch(choice){
        case 1: printf("Input data to insert: ");
                scanf("%d", &data);
                enqueue(&queue,data);
                break;
        case 2: data = dequeue(&queue);
                if(data != -9999){
                    printf("Deleted data %d\n", data);
                }
                else{
                    printf("Queue underflow\n");
                }
                break;
        case 3: printQueue(&queue);
                break;
        case 4: quit = 1;
                break;
        default:printf("Invalid option chosen, valid option is from 1 - 4\n");
        }
    }
    return 0;
}
