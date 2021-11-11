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
int loadFromFile(LinkedList *, char *, char);
void createListFromRandomNumbers(LinkedList *, int, char);
void insertAtTail(LinkedList *, int);
void insertAtHead(LinkedList *, int);
void printList(LinkedList *);
void printListDetail(LinkedList *);
void sortList(LinkedList *);
Node *find(LinkedList *, int, Node **);
int deleteFirst(LinkedList *);
int deleteLast(LinkedList *);
int deleteTarget(LinkedList *, int);
void reverse(LinkedList *);

void initList(LinkedList *listptr)
{
    listptr->head = NULL;
    listptr->tail = NULL;
    listptr->nodeCount = 0;
}

int loadFromFile(LinkedList *listPtr, char *fileName, char headTail)
{
    FILE *inputFile = fopen(fileName,"r");
    if(inputFile == NULL){
        return 0;
    }

    int data;
    fscanf(inputFile,"%d", &data);
    while(!feof(inputFile)){
        if(headTail == 'H' || headTail == 'h')
            insertAtHead(listPtr,data);
        else if(headTail == 'T' || headTail == 't')
            insertAtTail(listPtr,data);
        fscanf(inputFile,"%d", &data);
    }

    fclose(inputFile);
    return 1;
}

void createListFromRandomNumbers(LinkedList *listPtr, int n, char headTail)
{
    srand(time(NULL));

    for(int i = 1; i <= n; ++i){
        int k = rand() % 1000;

        if(headTail == 'H' || headTail == 'h')
            insertAtHead(listPtr,k);
        else if(headTail == 'T' || headTail == 't')
            insertAtTail(listPtr,k);
    }
}

void insertAtHead(LinkedList *listPtr, int data)
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

void insertAtTail(LinkedList *listptr, int data)
{
    Node *newNodePtr = (Node*) malloc(sizeof(Node));

    if(newNodePtr == NULL){
        printf("Unable to allocate new node\n");
        return;
    }

    newNodePtr->data = data;
    newNodePtr->next = NULL;

    if(listptr->nodeCount == 0){
        listptr->head = newNodePtr;
        listptr->tail = newNodePtr;
    }
    else{
        listptr->tail->next = newNodePtr;
        listptr->tail = newNodePtr;
    }
    listptr->nodeCount++;
}

void printList(LinkedList *listPtr)
{
    if(listPtr->nodeCount == 0){
        printf("Linked list is empty\n");
        return;
    }
    Node *current = listPtr->head;
    while( current != NULL){
        printf("%d \n", current->data);
        current = current->next;
    }
}

void printListDetail(LinkedList *listPrt)
{
    if(listPrt->nodeCount == 0){
        printf("Linked list is empty\n");
        return;
    }

    printf("Printing linked list in details\n");
    printf("Head: %p\n", listPrt->head);
    Node *current = listPrt->head;
    int counter = 1;
    while(current != NULL){
        printf("%d. (%p)[%d|%p]\n",counter, current, current->data, current->next);
        current = current->next;
        counter++;
    }
    printf("Tail: %p\n", listPrt->tail);
}

void sortList(LinkedList *listPtr)
{
    if(listPtr->nodeCount == 0)
        return;
    Node *current = listPtr->head, *index = NULL;
    int temp;
    while(current != NULL){
            index = current->next;
        while(index != NULL){
            if(current->data > index->data){
                temp = current->data;
                current->data = index->data;
                index->data = temp;
            }
            index = index->next;
        }
        current = current->next;
    }
}

Node *find(LinkedList *listPtr, int target, Node **prevPtr)
{
    Node *current = listPtr->head;
    *prevPtr = NULL;
    while(current != NULL){
        if(current->data == target){
            break;
        }
        *prevPtr = current;
        current = current->next;

    }
    return current;
}

int deleteFirst(LinkedList *listPtr)
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

int deleteLast(LinkedList *listPtr)
{
    if(listPtr->nodeCount == 0){
        return -9999;
    }

    Node *current = listPtr->head;
    Node *last = listPtr->tail;
    int data = last->data;

    if(listPtr->nodeCount == 1){
        listPtr->head = NULL;
        listPtr->tail = NULL;
    }
    else{
        while(current->next != last){
            current = current->next;
        }
        listPtr->tail = current;
        listPtr->tail->next = NULL;
    }

    free(last);
    listPtr->nodeCount--;
    return data;
}

int deleteTarget(LinkedList *listPtr, int target)
{
    Node *current, *prev = NULL;
    current = find(listPtr,target,&prev);

    if(current == NULL)
        return -9999;
    int data = current->data;

    if(current == listPtr->head)
        return deleteFirst(listPtr);
    else if(current == listPtr->tail)
        return deleteLast(listPtr);
    else{
        prev->next = current->next;
        free(current);
        listPtr->nodeCount--;
        return data;
    }
}

void reverse(LinkedList *listPtr)
{
    if(listPtr->nodeCount <= 1)
        return;

    Node *p, *q, *r;

    q = NULL;
    p = listPtr->head;
    r = p->next;

    while(1){
        p->next = q;
        if(p == listPtr->tail)
            break;

        q = p;
        p = r;
        r = r->next;
    }

    listPtr->tail = listPtr->head;
    listPtr->head = p;
}


void menu()
{
    printf("    Singly Linked List Operations\n");
    printf("----------------------------------------\n");
    printf("1. Load from file\n");          // load integer data from file and will create the list
                                          // by using insert_at_tail operation (menu option 3)
    printf("2. Create list with random numbers\n");
    printf("3. Insert at head\n");          // inserting a new node as the first node
    printf("4. Insert at tail\n");          // inserting a new node as the last node
    printf("5. Print List (detail)\n");     // printing the linked list in details,
                                          // including the data and pointer in each node
    printf("6. Print List (data only)\n");  // prints the integer data in each node
    printf("7. Find\n");                    // finds if an integer exisits in a node from
                                          // the start in the list
    printf("8. Delete first\n");            // deletes the first node
    printf("9. Delete last\n");             // deletes the last node
    printf("10.Delete a target node\n");    // deletes a particular node, if that exists
    printf("11.Reverse\n");                 // will physically reverse the list
    printf("12.Sort List\n");
    printf("13.Quit\n");                   // to terminate each node
}

int main()
{
    LinkedList list;
    initList(&list);
    menu();
    Node *current, *prev = NULL;
    int quit = 0, choice, data, success, n, target;
    char headTail = 0;

    while(!quit){
        printf("Please input your choice: ");
        scanf("%d", &choice);

        switch(choice){

        case 1: printf("Insert at head (as first node) or tail (as last node) (H/T) ?: ");
                scanf(" %c",&headTail);
                success = loadFromFile(&list,"files/data.txt",headTail);
                if(success == 1)
                    printf("File has been loaded successfully\n");
                else
                    printf("There was some error while loading and creating list");
                break;
        case 2: printf("Enter number of integer to be generated and added into the list: ");
                scanf("%d",&n);
                printf("Insert at head (as first node) or tail (as last node) (H/T) ?: ");
                scanf(" %c",&headTail);
                createListFromRandomNumbers(&list,n,headTail);
                break;
        case 3: printf("Input data to insert at head (as first node): ");
                scanf("%d",&data);
                insertAtHead(&list,data);
                break;
        case 4: printf("Input data to insert at tail (as last node): ");
                scanf("%d",&data);
                insertAtTail(&list,data);
                break;
        case 5: printListDetail(&list);
                break;
        case 6: printList(&list);
                break;
        case 7: printf("Enter target to find: ");
                scanf("%d",&data);
                current = find(&list,data, &prev);
                if(current == NULL)
                    printf("Target not found in the linked list\n");
                else
                    printf("Target node exists, address of the target node: %p, previous: %p\n",current,prev);
                break;
        case 8: data = deleteFirst(&list);
                if(data == -9999){
                    printf("Linked list is empty\n");
                }
                else{
                    printf("First node has been deleted, data %d\n", data);
                }
                break;
        case 9: data = deleteLast(&list);
                if(data == -9999){
                    printf("Linked list is empty\n");
                }
                else{
                    printf("Last node has been deleted, data %d\n", data);
                }
                break;
        case 10:printf("Enter target to delete: ");
                scanf("%d",&target);
                data = deleteTarget(&list,target);
                if(data == -9999){
                    printf("Target %d does not exist in the list\n", target);
                }
                else{
                    printf("Target node with data: %d, deleted successfully\n", data);
                }
                break;
        case 11:reverse(&list);
                break;
        case 12:sortList(&list);
                break;
        case 13:quit = 1;
                break;
        default: printf("Invalid option chosen, valid option is from 1-12\n");
        }
    }
    return 0;
}

