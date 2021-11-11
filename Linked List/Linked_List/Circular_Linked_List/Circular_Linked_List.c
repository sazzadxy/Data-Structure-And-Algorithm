#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node{
    int data;
    struct Node *next;
}Node;

typedef struct {
    struct Node *tail;
    int nodeCount;
}CircularLinkedList;

void initList(CircularLinkedList *);
int loadFromFile(CircularLinkedList *, char *, char);
void createListFromRandomNumbers(CircularLinkedList *, int);
void insertNode(CircularLinkedList *, int);
void printList(CircularLinkedList *);
Node *find(CircularLinkedList *, int);
int deleteNode(CircularLinkedList *);
void menu();

void initList(CircularLinkedList *listPtr)
{
    listPtr->tail = NULL;
    listPtr->nodeCount = 0;
}

void insertNode(CircularLinkedList *listPtr, int data)
{
    Node *newNodePtr = (Node *)malloc(sizeof(Node));
    if(newNodePtr == NULL)
    {
        printf("Unable to create node for the circular linked list\n");
        return;
    }
    newNodePtr->data = data;
    newNodePtr->next = NULL;

    if(listPtr->nodeCount == 0)
        newNodePtr->next = newNodePtr;
    else{
        newNodePtr->next = listPtr->tail->next;
        listPtr->tail->next = newNodePtr;
    }
    listPtr->tail = newNodePtr;
    listPtr->nodeCount++;
}

void createListFromRandomNumbers(CircularLinkedList *listPtr, int n)
{
    srand(time(NULL));

    for(int i  = 0; i < n; ++i){
        int k = rand() % 100;
        insertNode(listPtr,k);
    }
}

void menu()
{
    printf("    Circular Linked List Operations\n");
    printf("----------------------------------------\n");

    printf("1. Create list with random numbers\n");
    printf("2. Insert\n");          // inserting a new node as the first node
    printf("3. Delete\n");          // inserting a new node as the last node
    printf("4. Print List (data only)\n");  // prints the integer data in each node
    printf("5. Find\n");                    // finds if an integer exists in a node from
                                            // the start in the list
    printf("6. Quit\n");                   // to terminate each node
}

int deleteNode(CircularLinkedList *listPtr)
{
    if(listPtr->nodeCount == 0){
        return -9999;
    }
    Node *p = listPtr->tail->next;
    int data = p->data;

    if(listPtr->tail == listPtr->tail->next)  // listPtr->nodeCount == 1
        listPtr->tail = NULL;
    else{
        listPtr->tail->next = p->next;
    }
    free(p);
    listPtr->nodeCount--;
    return data;
}

void printList(CircularLinkedList *listPtr)
{
    if(listPtr->nodeCount == 0){
        printf("Linked list is empty\n");
        return;
    }

    int done = 0;
    Node *current = listPtr->tail->next;
    while(!done){
        printf("%4d",current->data);

        if(current == listPtr->tail)
            done = 1;
        else
            current = current->next;
    }
    printf("\n");
}

Node *find(CircularLinkedList *listPtr, int target)
{
    if(listPtr->nodeCount == 0)
        return NULL;

    Node *current = listPtr->tail->next;
    int done = 0;

    while(!done){
        if(current->data == target){
            return current;
        }
        if(current == listPtr->tail)
            done = 1;
        else
            current = current->next;
    }
    return NULL;
}

int main()
{
    CircularLinkedList list;
    initList(&list);
    menu();

    int choice, data, n, target, quit =  0;
    Node *current;

    while(!quit){
        printf("Please input your choice: ");
        scanf("%d",&choice);

        switch(choice){
        case 1: printf("Enter number of integers to be generated and added into the list: ");
                scanf("%d", &n);
                createListFromRandomNumbers(&list,n);
                break;
        case 2: printf("Input data to insert: ");
                scanf("%d", &data);
                insertNode(&list,data);
                break;
        case 3: data = deleteNode(&list);
                if(data == -9999){
                    printf("Linked list is empty\n");
                }
                else{
                    printf("First node has been deleted, data: %d\n", data);
                }
                break;
        case 4: printList(&list);
                break;
        case 5: printf("Enter target to find: ");
                scanf("%d", &target);
                current = find(&list,target);
                if(current == NULL)
                    printf("Target not found in the Linked list\n");
                else
                    printf("Target node exists, address of the target node: %p\n", current);
                break;
        case 6: quit = 1;
                break;
        default: printf("Invalid option chosen, valid option is from 1 - 11\n");
        }
    }
    return 0;
}
