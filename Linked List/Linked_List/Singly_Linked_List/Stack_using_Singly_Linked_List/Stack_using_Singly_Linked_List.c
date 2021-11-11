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
void push(LinkedList *, int);
void printList(LinkedList *);
int pop(LinkedList *);
void menu();

void initList(LinkedList *listPtr)
{
    listPtr->head = NULL;
    listPtr->tail = NULL;
    listPtr->nodeCount = 0;
}

void push(LinkedList *listPtr, int data)
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
        newNodePtr->next = listPtr->head;
        listPtr->head = newNodePtr;
    }
    listPtr->nodeCount++;
}

int pop(LinkedList *listPtr)
{
    if(listPtr->nodeCount == 0){
        return -9999;
    }

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

void printList(LinkedList *listPtr)
{
    if (listPtr->nodeCount == 0){
        printf("Stack is empty\n");
        return;
    }
    Node *current = listPtr->head;
    while(current != NULL){
        printf("%4d",current->data);
        current = current->next;
    }
    printf("\n");
}

void menu()
{
    printf("    Stack using LinkedList\n");
    printf("----------------------------------------\n");
    printf("1. Push\n");
    printf("2. Pop\n");
    printf("3. Display\n");
    printf("4. Quit\n");                   // to terminate each node
}

int main()
{
    LinkedList stack;
    initList(&stack);
    menu();
    int quit = 0;
    int data, choice;

    while(quit != 1){
        printf("Please input your choice: ");
        scanf("%d", &choice);
        switch(choice){
        case 1: printf("Input data to Push: ");
                scanf("%d", &data);
                push(&stack,data);
                break;
        case 2: data = pop(&stack);
                if(data == -9999){
                    printf("Stack underflow\n");
                }
                else{
                    printf("Popped data %d\n", data);
                }
                break;
        case 3: printList(&stack);
                break;
        case 4: quit = 1;
                break;
        default:printf("Invalid option chosen, valid option is from 1 - 4\n");
        }
    }
    return 0;
}
