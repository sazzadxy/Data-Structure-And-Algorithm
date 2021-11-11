#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int info;
    struct Node *next;
};

struct Node *createList(struct Node *start);
void displayList(struct Node *start);
void countNodes(struct Node *start);
void search(struct Node *start,int x);
struct Node *insertInBeginnig(struct Node *start,int data);
void insertAtEnd(struct Node *start,int data);
void insertAfter(struct Node *start,int data,int x);
struct Node *insertBefore(struct Node *start,int data,int x);
struct Node *insertAtPosition(struct Node *start,int data,int k);
struct Node *deleteNode(struct Node *start,int x);
struct Node *reverseList(struct Node *start);

int main()
{
    struct Node *start = NULL;
    int choice, data, x,k;

    start = createList(start);

    while(1)
    {
        printf("\n");
        printf("\tSingly Linked List\t\n");
        printf("\t------------------\t\n");
        printf("1.Display list\n");
        printf("2.Count the number of nodes\n");
        printf("3.Search for an element\n");
        printf("4.Add to empty list / Add at beginning\n");
        printf("5.Add a node at end of the list\n");
        printf("6.Add a node after a specific node\n");
        printf("7.Add a node before a specific node\n");
        printf("8.Add a node at a given position\n");
        printf("9.Delete a node\n");
        printf("10.Reverse the list\n");
        printf("11.Quit\n\n");
        printf("Enter your choice: ");
        scanf("%d",&choice);

        if(choice == 11)
            break;

        switch(choice)
        {
        case 1:
            displayList(start);
            break;
        case 2:
            countNodes(start);
            break;
        case 3:
            printf("Enter the element to be searched: ");
            scanf("%d",&data);
            search(start,data);
            break;
        case 4:
            printf("Enter the element to be inserted: ");
            scanf("%d",&data);
            start = insertInBeginnig(start,data);
            break;
        case 5:
            printf("Enter the element to be inserted: ");
            scanf("%d",&data);
            insertAtEnd(start,data);
            break;
        case 6:
            printf("Enter the element to be inserted: ");
            scanf("%d",&data);
            printf("Enter the element after which to insert: ");
            scanf("%d",&x);
            insertAfter(start,data,x);
            break;
        case 7:
            printf("Enter the element to be inserted: ");
            scanf("%d",&data);
            printf("Enter the element before which to insert: ");
            scanf("%d",&x);
            start = insertBefore(start,data,x);
            break;
        case 8:
            printf("Enter the element to be inserted: ");
            scanf("%d",&data);
            printf("Enter the position at which to insert: ");
            scanf("%d",&k);
            start = insertAtPosition(start,data,k);
            break;
        case 9:
            printf("Enter the element to be deleted: ");
            scanf("%d",&data);
            start = deleteNode(start,data);
            break;
        case 10:
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
    printf("List is: ");
    p = start;
    while(p != NULL)
    {
        printf("%d ",p->info);
        p = p->next;
    }
    printf("\n");
}

void countNodes(struct Node *start)
{
    struct Node *p = start;
    int n = 0;

    while(p != NULL)
    {
        n++;
        p = p->next;
    }
    printf("Number of nodes in list = %d\n",n);
}

void search(struct Node *start,int x)
{
    struct Node *p;
    int position = 1;
    p = start;

    while(p != NULL)
    {
        if(p->info == x)
            break;
        position++;
        p = p->next;
    }

    if(p == NULL)
        printf("%d not found in the list\n",x);
    else
        printf("%d is at position %d\n",x,position);
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

void insertAfter(struct Node *start,int data,int x)
{
    struct Node *temp, *p;

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
        temp->next = p->next;
        p->next = temp;
    }
}

struct Node *insertBefore(struct Node *start,int data,int x)
{
    struct Node *p, *temp;

    if(start == NULL)
    {
        printf("List is empty");
        return start;
    }

    // if x is in first node, node is to be inserted before first node
    if(x == start->info)
    {
        temp = (struct Node*)malloc(sizeof(struct Node));
        temp->info = data;
        temp->next = start;
        start = temp;
        return start;
    }

    // Find pointer to predecessor of node containing x
    p = start;
    while(p->next != NULL)
    {
        if(p->next->info == x)
            break;
        p = p->next;
    }

    if(p->next == NULL)
        printf("%d not present in the list\n",x);
    else
    {
        temp = (struct Node*)malloc(sizeof(struct Node));
        temp->info = data;
        temp->next = p->next;
        p->next = temp;
    }
    return start;
}

struct Node *insertAtPosition(struct Node *start,int data,int k)
{
    int i;
    struct Node *p, *temp;

    if(k == 1)
    {
        temp = (struct Node*)malloc(sizeof(struct Node));
        temp->info = data;
        temp->next = start;
        start = temp;
        return start;
    }

    p = start;
    for(i = 1; i < k-1 && p != NULL; i++) // find a pointer to k-1 node
        p = p->next;

    if(p == NULL)
        printf("You can insert only up to %dth position\n",i);
    else
    {
        temp = (struct Node*)malloc(sizeof(struct Node));
        temp->info = data;
        temp->next = p->next;
        p->next = temp;
    }
    return start;
}

struct Node *deleteNode(struct Node *start,int x)
{
    struct Node *temp, *p;
    if(start == NULL)
    {
        printf("List is empty\n");
        return start;
    }

    // Deletion of first node
    if(start->info == x)
    {
        temp = start;
        start = start->next;
        free(temp);
        return start;
    }

    // Deletion in between or at the end
    p = start;
    while(p->next != NULL)
    {
        if(p->next->info == x)
            break;
        p = p->next;
    }
    if(p->next == NULL)
        printf("Element %d not in list\n\n",x);
    else
    {
        temp = p->next;
        p->next = temp->next;
        free(temp);
    }
    return start;
}

struct Node *reverseList(struct Node *start)
{
    struct Node  *prev, *ptr, *next;
    prev = NULL;
    ptr = start;

    while(ptr != NULL)
    {
        next = ptr->next;
        ptr->next = prev;  // NULL
        prev = ptr;
        ptr = next;
    }
    start = prev;
    return start;
}
