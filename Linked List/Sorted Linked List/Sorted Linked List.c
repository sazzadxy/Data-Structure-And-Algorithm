#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int info;
    struct Node *next;
};

void displayList(struct Node *start);
void search(struct Node *start, int x);
struct Node *insertInOrder(struct Node *start, int data);

int main()
{
    int choice, data;
    struct Node *start = NULL;

    while(1)
    {
        printf("1.Display list\n");
        printf("2.Insert a new node\n");
        printf("3.Search\n");
        printf("4.Exit\n");
        printf("Enter your choice: ");
        scanf("%d",&choice);

        if(choice == 4)
            break;

        switch(choice)
        {
        case 1:
            displayList(start);
            break;
        case 2:
            printf("Enter the element to be inserted: ");
            scanf("%d",&data);
            start = insertInOrder(start,data);
            break;
        case 3:
            printf("Enter the element to be searched: ");
            scanf("%d",&data);
            search(start,data);
            break;
        default:
            printf("Wrong choice\n");
        }
    }
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

    p = start;
    while(p->next != NULL && p->next->info <= data)
        p = p->next;

    temp->next = p->next;
    p->next = temp;
    return start;
}

void search(struct Node *start, int x)
{
    struct Node *p;
    int position;

    if(start == NULL)
    {
        printf("List is empty\n");
        return;
    }

    p = start;
    position = 1;
    while(p != NULL && p->info <= x)
    {
        if(p->info == x)
            break;
        position++;
        p = p->next;
    }

    if(p == NULL || p->info != x)
        printf("%d not found in the list\n",x);
    else
        printf("%d at position %d\n",x,position);
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
