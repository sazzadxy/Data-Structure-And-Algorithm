
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
struct Node *concatenate(struct Node *start1, struct Node *start2);

int main()
{
    struct Node *start1, *start2 = NULL;

    start1 = createList(start2);
    start2 = createList(start2);

    printf("First list is: "); displayList(start1);
    printf("Second list is: "); displayList(start2);

    start1 = concatenate(start1,start2);
    printf("Concatenated list is: "); displayList(start1);

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

struct Node *insertInBeginnig(struct Node *start,int data)
{
    struct Node *temp;
    temp = (struct Node*)malloc(sizeof(struct Node));
    temp->info = data;

    temp->next = start;
    start = temp;

    return temp;
}

void insertAtEnd(struct Node *start,int data)
{
    struct Node *temp, *p;
    temp = (struct Node*)malloc(sizeof(struct Node));
    temp->info = data;

    p = start;
    while(p->next != NULL)
        p = p->next;

    p->next = temp;
    temp->next = NULL;
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

struct Node *concatenate(struct Node *start1, struct Node *start2)
{
    struct Node *p;

    if(start1 == NULL)
    {
        start1 = start2;
        return start1;
    }

    if(start2 == NULL)
        return start1;

    p = start1;
    while(p->next != NULL)
        p = p->next;

    p->next = start2;
    return start1;
}
