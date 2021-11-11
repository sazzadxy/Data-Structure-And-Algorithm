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
void createListFromRandomNumbers(LinkedList *, int);
void insertAtTail(LinkedList *, int);
void printList(LinkedList *);
void printListForward(LinkedList *);
void printListReverse(LinkedList *);
void printRecForward(Node *);
void printRecReverse(Node *);

void initList(LinkedList *listPtr)
{
    listPtr->head = NULL;
    listPtr->tail = NULL;
    listPtr->nodeCount = 0;
}

void createListFromRandomNumbers(LinkedList *listPtr, int n)
{
    srand(time(NULL));

    for(int i = 1; i <= n; ++i){
        int k = rand() % 1000;
        insertAtTail(listPtr,k);
    }
}

void insertAtTail(LinkedList *listPtr, int data)
{
    Node *newNodePtr = (Node *) malloc(sizeof(Node));

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

void printList(LinkedList *listPtr)
{
    if(listPtr->nodeCount == 0){
        printf("Linked list is empty\n");
        return;
    }
    Node *current = listPtr->head;
    printf("Linked list: ");
    while( current != NULL){
        printf("%d ", current->data);
        current = current->next;
    }
}

void printListForward(LinkedList *listPtr)
{
    printRecForward(listPtr->head);
}

void printListReverse(LinkedList *listPtr)
{
    printRecReverse(listPtr->head);
}

void printRecForward(Node *p)
{
    if(p == NULL)
        return;

    printf("%4d",p->data);
    printRecForward(p->next);
}

void printRecReverse(Node *p)
{
    if(p == NULL)
        return;

    printRecReverse(p->next);
    printf("%4d",p->data);

}

int main()
{
    LinkedList listPtr;
    initList(&listPtr);
    createListFromRandomNumbers(&listPtr,10);
    printList(&listPtr);
    printf("\n");
    printListForward(&listPtr);
    printf("\n");
    printListReverse(&listPtr);
    printf("\n");
    return 0;
}






















