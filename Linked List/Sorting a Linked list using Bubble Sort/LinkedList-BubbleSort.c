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
void sortByExchangingData(struct Node *start);
struct Node *sortByExchangingLinks(struct Node *start);

int main()
{
    struct Node *start1 = NULL, *start2 = NULL;

    printf("Create first list \n");
    start1 = createList(start1);
    sortByExchangingData(start1);
    displayList(start1);

    printf("Create second list \n");
    start2 = createList(start2);
    start2 = sortByExchangingLinks(start2);
    displayList(start2);

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

void sortByExchangingData(struct Node *start)
{
    struct Node *end, *p, *q;
    int temp;

    for(end = NULL; end != start->next; end = p)
    {
        for(p = start; p->next != end; p = p->next)
        {
            q = p->next;
            if(p->info > q->info)
            {
                temp = p->info;
                p->info = q->info;
                q->info = temp;
            }
        }
    }
}

struct Node *sortByExchangingLinks(struct Node *start)
{
    struct Node *end, *temp, *r, *p, *q;

    for(end = NULL; end != start->next; end = p)
    {
        for(r = p = start; p->next != end; r = p, p = p->next)
        {
            q = p->next;
            if(p->info > q->info)
            {
                p->next = q->next;
                q->next = p;
                if(p != start)
                    r->next = q;
                else
                    start = q;
                temp = p;
                p = q;
                q = temp;
            }
        }
    }
    return start;
}
