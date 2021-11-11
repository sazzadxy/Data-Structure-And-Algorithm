
#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int info;
    struct Node *next;
};

void displayList(struct Node *start);
struct Node *createSortedList(struct Node *start);
struct Node *insertInOrder(struct Node *start, int data);
struct Node *merge(struct Node *p1, struct Node *p2);

int main()
{
    struct Node *start1 = NULL, *start2 = NULL, *startM;

    start1 = createSortedList(start1);
    start2 = createSortedList(start2);

    printf("List1: ");
    displayList(start1);

    printf("List2: ");
    displayList(start2);

    startM = merge(start1,start2);
    printf("Merged List: ");
    displayList(startM);

    return 0;
}

struct Node *insertInOrder(struct Node *start, int data)
{
    struct Node *p, *temp;

    temp = (struct Node*)malloc(sizeof(struct Node));
    temp->info = data;

    // List empty or new node to be inserted before first node
    if(start == NULL || data < start->info)
    {
        temp->next = start;
        start = temp;
        return start;
    }
    else
    {
        p = start;
        while(p->next != NULL && p->next->info <= data)
            p = p->next;

        temp->next = p->next;
        p->next = temp;
    }

    return start;
}

struct Node *createSortedList(struct Node *start)
{
    int i, n, data;
    printf("Enter the number of nodes: ");
    scanf("%d",&n);

    for(i = 1; i <= n; i++)
    {
        printf("Enter the element to be inserted: ");
        scanf("%d",&data);
        start = insertInOrder(start,data);
    }
    return start;
}

struct Node *merge(struct Node *p1, struct Node *p2)
{
    struct Node *pM, *startM;

    if(p1->info <= p2->info)
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

void displayList(struct Node *start)
{
    struct Node *p = NULL;
    if(start == NULL)
    {
        printf("List is empty\n");
        return;
    }

    p = start;
    while(p != NULL)
    {
        printf("%d ",p->info);
        p = p->next;
    }
    printf("\n");
}

