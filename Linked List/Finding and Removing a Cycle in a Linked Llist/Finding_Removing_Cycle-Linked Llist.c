// Hare and Tortoise Algorithm (Floyd's Cycle Detection Algorithm)

#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int info;
    struct Node *next;
};

struct Node *createList(struct Node *start);
void displayList(struct Node *start);
struct Node *insertInBeginnig(struct Node *start,int data);
void insertAtEnd(struct Node *start,int data);

void insertCycle(struct Node *start, int x);
struct Node *findCycle(struct Node *start);
void removeCycle(struct Node *start, struct Node *pC);

int main()
{
    int x;
    struct Node *start = NULL, *ptr;

    start = createList(start);

    if(start == NULL)
        exit(1);

    //x = 40;
    printf("Enter the node where cycle forms: ");
    scanf("%d",&x);
    insertCycle(start,x);

    ptr = findCycle(start);

    if(ptr == NULL)
        printf("List is NULL terminated\n");
    else
    {
        printf("Cycle found in the list\n");
        removeCycle(start,ptr);
        printf("Cycle removed, now list is NULL terminated\n");
    }
    displayList(start);
    return 0;
}

void displayList(struct Node *start)
{
    struct Node *p = NULL;
    if(start == NULL)
    {
        printf("List is empty\n");
        return;
    }
    printf("List is: ");
    p = start;
    while(p != NULL)
    {
        printf("%d ",p->info);
        p = p->next;
    }
    printf("\n");
}

struct Node *createList(struct Node *start)
{
    int i, n, data;
    printf("Enter the number of nodes: ");
    scanf("%d",&n);

    if(n == 0)
        return start;

    printf("Enter the first element to be inserted: ");
    scanf("%d",&data);
    start = insertInBeginnig(start,data);

    for(i = 2; i <= n; i++)
    {
        printf("Enter the next element to be inserted: ");
        scanf("%d",&data);
        insertAtEnd(start,data);
    }
    return start;
}

struct Node *insertInBeginnig(struct Node *start,int data)
{
    struct Node *temp;
    temp = (struct Node*)malloc(sizeof(struct Node));
    temp->info = data;

    temp->next = start;
    start = temp;

    return start;
}

void insertAtEnd(struct Node *start,int data)
{
    struct Node *p, *temp;
    temp = (struct Node*)malloc(sizeof(struct Node));
    temp->info = data;

    p = start;
    while(p->next != NULL)
        p = p->next;

    p->next = temp;
    temp->next = NULL;
}

void insertCycle(struct Node *start, int x)
{
    struct Node *p, *px = NULL, *prev;

    p = start;
    while(p!=NULL)
    {
        if(p->info == x)
            px = p;  // assign cycle node px
        prev = p;    // prev, previous node of p
        p = p->next; // visited till last node becomes null, p becomes NULL, prev is last node
    }

    if(px != NULL)   // prev points to last node
        prev->next = px; // last node points to px to form cycle
}

/* Returns NULL if the list is NULL terminated otherwise
   returns pointer to node where both slow and fast pointers meet */
struct Node *findCycle(struct Node *start)
{
    struct Node *fastP, *slowP;

    if(start->next == NULL) // Only one element
        return NULL;

    slowP = fastP = start;

    while(fastP != NULL && fastP->next != NULL)  // even number of nodes && odd  numbers of node
    {
        slowP = slowP->next;  // moves one node at a time
        fastP = fastP->next->next; // moves two node at a time
        if(slowP == fastP)   // detects cycle where slow and fast node meet
            return slowP;
    }
    return NULL;
}

void removeCycle(struct Node *start, struct Node *pC)
{
    struct Node *p, *q;
    int i, lenCycle, lenRemList, lengthList;

    printf("Node at which the cycle was detected is %d\n",pC->info);

    p = q = pC;
    lenCycle = 0;
    do   // because of p = q = pC, while loop won't work here
    {
        lenCycle++;
        q = q->next;
    }while(p != q);
    printf("Length of cycle is: %d\n",lenCycle);

    lenRemList = 0;
    p = start;
    while(p != q)
    {
        lenRemList++;
        p = p->next;
        q = q->next;
    }
    printf("Number of nodes not included in the cycle are: %d\n",lenRemList);

    lengthList = lenCycle + lenRemList;
    printf("Length of the list is: %d\n",lengthList);

    p = start;
    for(i = 1; i <= lengthList-1; i++)
        p = p->next;
    p->next = NULL; // assign last node to null to remove cycle
}

