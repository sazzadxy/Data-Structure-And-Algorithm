#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node{
    int data;
    struct Node *next;
    struct Node *prev;
}Node;

typedef struct {
    struct Node *head;
    struct Node *tail;
    int nodeCount;
}DBLinkedList;

void initList(DBLinkedList *);
void addFirst(DBLinkedList *, int);
void addLast(DBLinkedList *, int);
int deleteFirst(DBLinkedList *);
int deleteLast(DBLinkedList *);
void printList(DBLinkedList *);
void menu();

void menu()
{
    printf("    Double Ended Queue Operations\n");
    printf("----------------------------------------\n");
    printf("1. Insert at front\n");          // load integer data from file and will create the list
    // by using insert_at_tail operation (menu option 3)
    printf("2. Insert at rear\n");
    printf("3. Delete front\n");          // inserting a new node as the first node
    printf("4. Delete Rear\n");          // inserting a new node as the last node
    printf("5. Display\n");
    printf("6. Quit\n");                   // to terminate each node
}

int main()
{
    DBLinkedList deq;
    initList(&deq);
    menu();
    int quit = 0;
    int choice, data;

    while(!quit){
        printf("Please input your choice: ");
        scanf("%d", &choice);
        switch(choice){
        case 1: printf("Input data to insert at head (as first node): ");
                scanf("%d", &data);
                addFirst(&deq,data);
                break;
        case 2: printf("Input data to insert at tail (as last node): ");
                scanf("%d", &data);
                addLast(&deq, data);
                break;
        case 3: if(deq.nodeCount > 0){
                    data = deleteFirst(&deq);
                    printf("Deleted data from front: %d\n", data);
                }
                else{
                    printf("Underflow, DEQ is empty\n");
                }
                break;
        case 4:if(deq.nodeCount > 0){
                    data = deleteLast(&deq);
                    printf("Deleted data from front: %d\n", data);
                }
                else{
                    printf("Underflow, DEQ is empty\n");
                }
                break;
        case 5: printList(&deq);
                break;
        case 6: quit = 1;
                break;
        default: printf("Invalid option chosen, valid option is from 1 - 5\n");
        }
    }

    return 0;
}

void initList(DBLinkedList *listPtr)
{
    listPtr->head = listPtr->tail = NULL;
    listPtr->nodeCount = 0;
}

void addFirst(DBLinkedList *listPtr, int data)
{
    Node *p = (Node *)malloc(sizeof(Node));

    if(p == NULL){
        printf("Unable to create node for the doubly linked list\n");
        return;
    }
    p->data = data;
    p->next = p->prev =  NULL;

    if(listPtr->nodeCount == 0){
        listPtr->head = listPtr->tail = p;
    }
    else{
        p->next = listPtr->head;
        listPtr->head->prev = p;
        listPtr->head = p;
    }
    listPtr->nodeCount++;
}

void addLast(DBLinkedList *listPtr, int data)
{
    Node *p = (Node *) malloc(sizeof(Node));

    if(p == NULL){
        printf("Unable to create node for the doubly linked list\n");
        return;
    }
    p->data = data;
    p->next = p->prev = NULL;

    if(listPtr->nodeCount == 0)
        listPtr->head = listPtr->tail = p;
    else{
        p->prev = listPtr->tail;
        listPtr->tail->next = p;
        listPtr->tail = p;
    }
    listPtr->nodeCount++;
}

int deleteFirst(DBLinkedList *listPtr)
{
    if(listPtr->nodeCount == 0)
        return -999;

    Node *p = listPtr->head;
    if(listPtr->nodeCount == 1)
        listPtr->head = listPtr->tail = NULL;
    else{
        listPtr->head = listPtr->head->next;
        listPtr->head->prev = NULL;
    }
    int data = p->data;
    free(p);
    listPtr->nodeCount--;
    return data;
}

int deleteLast(DBLinkedList *listPtr)
{
    if(listPtr->nodeCount == 0)
        return -999;

    Node *p = listPtr->tail;
    if(listPtr->nodeCount == 1)
        listPtr->head = listPtr->tail = NULL;
    else{
        listPtr->tail = listPtr->tail->prev;
        listPtr->tail->next = NULL;
    }
    int data = p->data;
    free(p);
    listPtr->nodeCount--;
    return data;
}

void printList(DBLinkedList *listPtr)
{
    if (listPtr->nodeCount == 0){
        printf("Queue is empty\n");
        return;
    }
    Node *current = listPtr->head;
    while(current != NULL){
        printf("%4d",current->data);
        current = current->next;
    }
    printf("\n");
}
