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
int loadFromFile(DBLinkedList *, char *, char);
void createListFromRandomNumbers(DBLinkedList *, int, char);
void addFirst(DBLinkedList *, int);
void addLast(DBLinkedList *, int);
void printListDetail(DBLinkedList *);
Node *find(DBLinkedList *, int);
int insertAfter(DBLinkedList *, int, int);
int insertBefore(DBLinkedList *, int, int);
void printForward(DBLinkedList *);
void printReverse(DBLinkedList *);
int deleteFirst(DBLinkedList *);
int deleteLast(DBLinkedList *);
int deleteTarget(DBLinkedList *, int);
void reverse(DBLinkedList *);
void menu();

void initList(DBLinkedList *listPtr)
{
    listPtr->head = NULL;
    listPtr->tail = NULL;
    listPtr->nodeCount = 0;
}

void createListFromRandomNumbers(DBLinkedList *listPtr, int n, char headTail)
{
    srand(time(NULL));

    for(int i = 1; i <= n; ++i){
        int k = rand() % 1000;

        if(headTail == 'H' || headTail == 'h')
            addFirst(listPtr,k);
        else if(headTail == 'T' || headTail == 't')
            addLast(listPtr,k);
    }
}

int loadFromFile(DBLinkedList *listPtr, char *fileName, char headTail)
{
    FILE *f = fopen(fileName,"r");
    if(f == NULL){
        return 0;
    }

    int data;
    fscanf(f,"%d",&data);
    while(!feof(f)){
        if(headTail == 'H' || headTail == 'h')
            addFirst(listPtr,data);
        else if(headTail == 'T' || headTail == 't')
            addLast(listPtr,data);
        fscanf(f,"%d", &data);
    }
    fclose(f);
    return 1;
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

void printForward(DBLinkedList *listPtr)
{
    Node *p = listPtr->head;
    if(p == NULL){
        printf("Linked list is empty\n");
        return;
    }
    printf("Content of the double linked list: \n");
    while(p != NULL){
        printf("%4d", p->data);
        p = p->next;
    }
    printf("\n-- End --\n");
}

void printReverse(DBLinkedList *listPtr)
{
    Node *p = listPtr->tail;
    if(p == NULL){
        printf("Linked list is empty\n");
        return;
    }
    printf("Content of the double linked list in the reverse order: \n");
    while(p != NULL){
        printf("%4d", p->data);
        p = p->prev;
    }
    printf("\n-- End --\n");
}

Node *find(DBLinkedList *listPtr, int target)
{
    Node *p;

    for(p = listPtr->head; p != NULL; p = p->next){ // or p = listPtr->tail; p != NULL; p = p->prev
        if(p->data == target)
            return p;
    }
    return NULL;
}

int insertAfter(DBLinkedList *listPtr, int target, int data)
{
    Node *p = find(listPtr,target);

    if(p == NULL)
        return 0;

    if(p == listPtr->tail)
        addLast(listPtr,data);
    else{
        Node *q = (Node*) malloc(sizeof(Node));
        q->data = data;

        if(p == NULL){
            printf("Unable to create node\n");
            return 0;
        }

        q->next = p->next;
        p->next = q;
        q->prev = p;
        q->next->prev = q; // (q->next)->prev = q
    }
    listPtr->nodeCount++;
    return 1;
}

int insertBefore(DBLinkedList *listPtr, int target, int data)
{
    Node *p = find(listPtr,target);

    if(p == NULL)
        return 0;

    if(p == listPtr->head)
        addFirst(listPtr,data);
    else{
        Node *q = (Node*) malloc(sizeof(Node));
        q->data = data;

        if(p == NULL){
            printf("Unable to create node\n");
            return 0;
        }

        q->prev = p->prev;
        p->prev = q;
        q->next = p;
        q->prev->next = q; // (q->prev)->next = q
    }
    listPtr->nodeCount++;
    return 1;
}

int deleteFirst(DBLinkedList *listPtr)
{
    if(listPtr->nodeCount == 0)
        return 0;

    Node *p = listPtr->head;
    if(listPtr->nodeCount == 1)
        listPtr->head = listPtr->tail = NULL;
    else{
        listPtr->head = listPtr->head->next;
        listPtr->head->prev = NULL;
    }
    free(p);
    listPtr->nodeCount--;
    return 1;
}

int deleteLast(DBLinkedList *listPtr)
{
    if(listPtr->nodeCount == 0)
        return 0;

    Node *p = listPtr->tail;
    if(listPtr->nodeCount == 1)
        listPtr->head = listPtr->tail = NULL;
    else{
        listPtr->tail = listPtr->tail->prev;
        listPtr->tail->next = NULL;
    }
    free(p);
    listPtr->nodeCount--;
    return 1;
}

int deleteTarget(DBLinkedList *listPtr, int target)
{
    Node *p = find(listPtr, target);
    if(p == NULL)
        return 0;

    if(p == listPtr->head)
        return deleteFirst(listPtr);
    else if(p == listPtr->tail)
        return deleteLast(listPtr);
    else{
        p->prev->next = p->next;
        p->next->prev = p->prev;
        free(p);
        listPtr->nodeCount--;
        return 1;
    }
}

void printListDetail(DBLinkedList *listPtr)
{
     if(listPtr->nodeCount == 0){
        printf("Linked list is empty\n");
        return;
    }

    printf("Printing linked list in details\n");
    printf("Head: %p\n", listPtr->head);

    Node *current = listPtr->head;
    int counter = 1;
    while(current != NULL){
        printf("%d. (%p)[%d|%p]\n",counter, current, current->data, current->next);
        current = current->next;
        counter++;
    }
    printf("Tail: %p\n", listPtr->tail);
}

void menu()
{
    printf("    Doubly Linked List Operations\n");
    printf("----------------------------------------\n");
    printf("1. Load from file\n");          // load integer data from file and will create the list
                                            // by using insert_at_tail operation (menu option 3)
    printf("2. Create list with random numbers\n");
    printf("3. Add First\n");          // inserting a new node as the first node
    printf("4. Add Last\n");          // inserting a new node as the last node
    printf("5. Print List (detail)\n");     // printing the linked list in details,
                                            // including the data and pointer in each node
    printf("6. Print List first to last (data only)\n");  // prints the integer data in each node from the first node to last
    printf("7. Print List last to first (data only)\n");  // prints data fro last to the first node
    printf("8. Find\n");                                  // finds if an integer exisits in a node from
                                                          // the start in the list
    printf("9. Insert After\n");
    printf("10. Insert Before\n");
    printf("11. Delete first\n");            // deletes the first node
    printf("12. Delete last\n");             // deletes the last node
    printf("13. Delete a target node\n");    // deletes a particular node, if that exists

    printf("14. Quit\n");                   // to terminate each node
}

int main()
{
    DBLinkedList list;
    initList(&list);
    int choice = 0;
    menu();

    int quit, data, n, target, success;
    Node *current = NULL;
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
                addFirst(&list,data);
                break;
        case 4: printf("Input data to insert at tail (as last node): ");
                scanf("%d",&data);
                addLast(&list,data);
                break;
        case 5: printListDetail(&list);
                break;
        case 6: printForward(&list);
                break;
        case 7: printReverse(&list);
                break;
        case 8: printf("Enter target: ");
                scanf("%d",&target);
                current = find(&list,target);
                if(current == NULL)
                    printf("Linked list does not contain the target specified\n");
                else
                    printf("Target exists in the linked list, address: %p\n",current);
                break;
        case 9: printf("Enter target: ");
                scanf("%d",&target);
                printf("input data: ");
                scanf("%d",&data);
                if(insertAfter(&list,target,data) == 1)
                    printf("Insert after was successful\n");
                else
                    printf("Insert after failed\n");
                break;
        case 10: printf("Enter target: ");
                scanf("%d",&target);
                printf("input data: ");
                scanf("%d",&data);
                if(insertBefore(&list,target,data) == 1)
                    printf("Insert before was successful\n");
                else
                    printf("Insert before failed\n");
                break;
        case 11:if(deleteFirst(&list))
                    printf("First node deleted successfully\n");
                else
                    printf("Unable to delete first node\n");
                break;
        case 12:if(deleteLast(&list))
                    printf("Last node deleted successfully\n");
                else
                    printf("Unable to delete last node\n");
                break;
        case 13:printf("Enter target: ");
                scanf("%d",&target);
                if(deleteTarget(&list,target))
                    printf("Target node deleted successfully\n");
                else
                    printf("Unable to delete target node, target node may not be available\n");
                break;
        case 14:quit = 1;
                break;
        default: printf("Invalid option chosen, valid option is from 1-14\n");

        }
    }

    return 0;
}
