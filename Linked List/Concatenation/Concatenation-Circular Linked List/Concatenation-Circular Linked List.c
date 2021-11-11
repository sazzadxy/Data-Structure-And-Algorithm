#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int info;
    struct Node *next;
};

struct Node *createList(struct Node *last);
void displayList(struct Node *last);
struct Node *insertInEmptyList(struct Node *last,int data);
struct Node *insertInBeginnig(struct Node *last,int data);
struct Node *insertAtEnd(struct Node *last,int data);
struct Node *concatenate(struct Node *last1, struct Node *last2);

int main()
{
    struct Node *last1 = NULL, *last2 = NULL;

    last1 = createList(last1);
    last2 = createList(last2);

    printf("First list is: "); displayList(last1);
    printf("Second list is: "); displayList(last2);

    last1 = concatenate(last1,last2);
    printf("Concatenated list is: "); displayList(last1);
    return 0;
}

void displayList(struct Node *last)
{
    struct Node *p = NULL;
    if(last == NULL)
    {
        printf("List is empty\n");
        return;
    }

    p = last->next;
    do
    {
        printf("%d ",p->info);
        p = p->next;
    }while(p != last->next);
    printf("\n");
}

struct Node *insertInEmptyList(struct Node *last,int data)
{
    struct Node *temp;
    temp = (struct Node*)malloc(sizeof(struct Node));
    temp->info = data;

    last = temp;
    last->next = last;
    return last;
}

struct Node *insertAtEnd(struct Node *last,int data)
{
    struct Node *temp;
    temp = (struct Node*)malloc(sizeof(struct Node));
    temp->info = data;

    temp->next = last->next;
    last->next = temp;
    last = temp;
    return last;
}

struct Node *createList(struct Node *last)
{
    int i, n, data;

    printf("Enter the number of nodes: ");
    scanf("%d",&n);
    last = NULL;

    if(n == 0)
        return last;

    printf("Enter the first element to be inserted: ");
    scanf("%d",&data);
    last = insertInEmptyList(last,data);

    for(i = 2; i <= n; i++)
    {
        printf("Enter the next element to be inserted: ");
        scanf("%d",&data);
        last = insertAtEnd(last,data);
    }
    return last;
}

struct Node *concatenate(struct Node *last1, struct Node *last2)
{
    struct Node *p;

    if(last1 == NULL)
    {
        last1 = last2;
        return last1;
    }

    if(last2 == NULL)
        return last1;

    p = last1->next;
    last1->next = last2->next;
    last2->next = p;
    last1 = last2;

    return last1;
}


