#include <stdio.h>
#include <stdlib.h>

struct Node
{
    struct Node *prev;
    int info;
    struct Node *next;
};

struct Node *createList(struct Node *start);
void displayList(struct Node *start);
struct Node *insertInEmptyList(struct Node *start,int data);
struct Node *insertInBeginnig(struct Node *start,int data);
void insertAtEnd(struct Node *start,int data);
void insertAfter(struct Node *start,int data,int x);
struct Node *insertBefore(struct Node *start,int data,int x);
struct Node *deleteNode(struct Node *start,int x);
struct Node *reverseList(struct Node *start);

int main()
{
    struct Node *start = NULL;
    int choice, data, x;

    start = createList(start);

    while(1)
    {
        printf("\n");
        printf("\tDoubly Linked List\t\n");
        printf("\t------------------\t\n");
        printf("1.Display list\n");
        printf("2.Insert in empty list\n");
        printf("3.Insert a node in beginning of the list\n");
        printf("4.Insert a node at end of the list\n");
        printf("5.Insert a node after a specific node\n");
        printf("6.Insert a node before a specific node\n");
        printf("7.Delete a node\n");
        printf("8.Reverse the list\n");
        printf("9.Quit\n");
        printf("Enter your choice: ");
        scanf("%d",&choice);

        if(choice == 9)
            break;

        switch(choice)
        {
        case 1:
            displayList(start);
            break;
        case 2:
            printf("Enter the element to be inserted: ");
            scanf("%d",&data);
            start = insertInEmptyList(start,data);
            break;
        case 3:
            printf("Enter the element to be inserted: ");
            scanf("%d",&data);
            start = insertInBeginnig(start,data);
            break;
        case 4:
            printf("Enter the element to be inserted: ");
            scanf("%d",&data);
            insertAtEnd(start,data);
            break;
        case 5:
            printf("Enter the element to be inserted: ");
            scanf("%d",&data);
            printf("Enter the element after which to insert: ");
            scanf("%d",&x);
            insertAfter(start,data,x);
            break;
        case 6:
            printf("Enter the element to be inserted: ");
            scanf("%d",&data);
            printf("Enter the element before which to insert: ");
            scanf("%d",&x);
            start = insertBefore(start,data,x);
            break;
        case 7:
            printf("Enter the element to be deleted: ");
            scanf("%d",&data);
            start = deleteNode(start,data);
            break;
        case 8:
            start = reverseList(start);
            break;
        default:
            printf("Wrong choice\n");
        }
    }
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

    p = start;
    printf("List is :\n");
    while(p != NULL)
    {
        printf("%d ",p->info);
        p = p->next;
    }
    printf("\n");
}

struct Node *insertInEmptyList(struct Node *start,int data)
{
    struct Node *temp;
    temp = (struct Node*)malloc(sizeof(struct Node));
    temp->info = data;

    temp->prev = temp->next = NULL;
    start = temp;
    return start;
}

struct Node *insertInBeginnig(struct Node *start,int data)
{
    struct Node *temp;
    temp = (struct Node*)malloc(sizeof(struct Node));
    temp->info = data;

    temp->prev = NULL;
    temp->next = start;
    start->prev = temp;
    start = temp;
    return start;
}

void insertAtEnd(struct Node *start,int data)
{
    struct Node *temp,*p;
    temp = (struct Node*)malloc(sizeof(struct Node));
    temp->info = data;

    p = start;
    while(p->next != NULL)
        p = p->next;

    p->next = temp;
    temp->next = NULL;
    temp->prev = p;
}

struct Node *createList(struct Node *start)
{
    int i, n, data;

    printf("Enter the number of nodes: ");
    scanf("%d",&n);
    start = NULL;

    if(n == 0)
        return start;

    printf("Enter the first element to be inserted: ");
    scanf("%d",&data);
    start = insertInEmptyList(start,data);

    for(i = 2; i <= n; i++)
    {
        printf("Enter the next element to be inserted: ");
        scanf("%d",&data);
        insertAtEnd(start,data);
    }
    return start;
}

void insertAfter(struct Node *start,int data,int x)
{
    struct Node *p, *temp;

    temp = (struct Node*)malloc(sizeof(struct Node));
    temp->info = data;

    p = start;
    while(p != NULL)
    {
        if(p->info == x)
            break;
        p = p->next;
    }

    if(p == NULL)
        printf("%d not present in the list\n",x);
    else
    {
        temp->prev = p;
        temp->next = p->next;
        if(p->next != NULL)  // should not be done when p points to last node, otherwise p->next->prev = NULL gives error
            p->next->prev = temp;
        p->next = temp;
    }
}

struct Node *insertBefore(struct Node *start,int data,int x)
{
    struct Node *temp, *p;

    if(start == NULL)
    {
        printf("List is empty\n");
        return start;
    }

    if(start->info == x)
    {
        temp = (struct Node*)malloc(sizeof(struct Node));
        temp->info = data;

        temp->prev = NULL;
        temp->next = start;
        start->prev = temp;
        start = temp;
        return start;
    }

    p = start;
    while(p != NULL)
    {
        if(p->info == x)
            break;
        p = p->next;
    }

    if(p == NULL)
        printf("%d not present in the list\n",x);
    else
    {
        temp = (struct Node*)malloc(sizeof(struct Node));
        temp->info = data;

        temp->prev = p->prev;
        temp->next = p;
        p->prev->next = temp;
        p->prev = temp;
    }
    return start;
}

struct Node *deleteNode(struct Node *start,int x)
{
    struct Node *temp;

    if(start == NULL)
    {
        printf("List is empty\n");
        return start;
    }

    if(start->next == NULL)
    {
        if(start->info == x)  // only one node in the list
        {
            temp = start;
            start = NULL;
            free(temp);
        }
        else
            printf("%d not found in the list\n",x);
        return start;
    }

    // Deletion of first node
    if(start->info == x)
    {
        temp = start;
        start = start->next;
        start->prev = NULL;
        free(temp);
        return start;
    }

    temp = start->next;
    while(temp->next != NULL)
    {
        if(temp->info == x)
            break;
        temp = temp->next;
    }

    if(temp->next != NULL) // node to be deleted is in between
    {
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        free(temp);
    }
    else  // temp points to last node
    {
        if(temp->info == x) // node to be deleted is last node
        {
            temp->prev->next = NULL;
            free(temp);
        }
        else
            printf("Element %d not found in the list\n",x);
    }
    return start;
}

struct Node *reverseList(struct Node *start)
{
    struct Node *p1,*p2;

    if(start == NULL)
        return start;

    p1 = start;
    p2 = p1->next;
    p1->next = NULL;
    p1->prev = p2;

    while(p2 != NULL)
    {
        p2->prev = p2->next;
        p2->next = p1;
        p1 = p2;
        p2 = p2->prev;
    }
    start = p1;
    return start;
}



