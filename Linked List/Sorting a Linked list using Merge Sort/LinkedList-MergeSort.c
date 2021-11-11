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
struct Node *mergeSort(struct Node *p);
struct Node *divideList(struct Node *p);
struct Node *merge(struct Node *p, struct Node  *q);

int main()
{
    struct Node *start = NULL;
    start = createList(start);
    start = mergeSort(start);
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

struct Node *mergeSort(struct Node *start)
{
    struct Node *start1, *start2, *startM;

    if(start == NULL || start->next == NULL) // if list is empty or has one element
        return start;

    start1 = start;
    start2 = divideList(start);
    start1 = mergeSort(start1);
    start2 = mergeSort(start2);
    startM = merge(start1,start2);
    return startM;
}

struct Node *divideList(struct Node *p)
{
    struct Node *q, *start2;

    q = p->next->next; // 3rd node
    while(q != NULL && q->next != NULL) // if list has even number of nodes && list has odd number of nodes
    {
        p = p->next;       // Moving one node at a time
        q = q->next->next; // Moving two node at a time
    }
    start2 = p->next;
    p->next = NULL;
    return start2;
}

struct Node *merge(struct Node *p1, struct Node  *p2)
{
    struct Node *startM, *pM;

    if(p1->info < p2->info)
    {
        startM = p1;
        p1 = p1->next;
    }
    else
    {
        startM = p2;
        p2 = p2->next;
    }

    pM = startM;
    while(p1 != NULL && p2 != NULL)
    {
        if(p1->info <= p2->info)
        {
            pM->next = p1;
            pM = pM->next;
            p1 = p1->next;
        }
        else
        {
            pM->next = p2;
            pM = pM->next;
            p2 = p2->next;
        }
    }

    if(p1 == NULL)
        pM->next = p2;
    else
        pM->next = p1;

    return startM;
}
