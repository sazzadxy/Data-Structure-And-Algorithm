
#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int info;
    struct Node *next;
};

void createList(struct Node *head);
void displayList(struct Node *head);
void insertAtEnd(struct Node *head,int data);
void insertBefore(struct Node *head,int data,int x);
void insertAtPosition(struct Node *head,int data,int k);
void deleteNode(struct Node *head,int x);
void reverse(struct Node *head);

int main()
{
    struct Node *head;
    int choice, data, x,k;

    head = (struct Node*)malloc(sizeof(struct Node));
    head->info = 0;
    head->next = NULL;

    createList(head);

    while(1)
    {
        printf("\n");
        printf("\tSingly Linked List With Header Node\t\n");
        printf("\t-----------------------------------\t\n");
        printf("1.Display list\n");
        printf("2.Add a node at the end of the list\n");
        printf("3.Add a new node before node\n");
        printf("4.Insert at a given position\n");
        printf("5.Delete a node\n");
        printf("6.Reverse the list\n");
        printf("7.Quit\n\n");
        printf("Enter your choice: ");
        scanf("%d",&choice);

        if(choice == 7)
            break;

        switch(choice)
        {
        case 1:
            displayList(head);
            break;
        case 2:
            printf("Enter the element to be inserted: ");
            scanf("%d",&data);
            insertAtEnd(head,data);
            break;
        case 3:
            printf("Enter the element to be inserted: ");
            scanf("%d",&data);
            printf("Enter the element before which to insert: ");
            scanf("%d",&x);
            insertBefore(head,data,x);
            break;
        case 4:
            printf("Enter the element to be inserted: ");
            scanf("%d",&data);
            printf("Enter the element after which to insert: ");
            scanf("%d",&k);
            insertAtPosition(head,data,k);
            break;
        case 5:
            printf("Enter the element to be deleted: ");
            scanf("%d",&data);
            deleteNode(head,data);
            break;
        case 6:
            reverse(head);
            break;
        default:
            printf("Wrong choice\n");
        }
    }
    return 0;
}

void displayList(struct Node *head)
{
    struct Node *p;
    if(head->next == NULL)
    {
        printf("List is empty\n");
        return;
    }
    printf("List is: ");
    p = head->next;
    while(p != NULL)
    {
        printf("%d ",p->info);
        p = p->next;
    }
    printf("\n");
}


void insertAtEnd(struct Node *head,int data)
{
    struct Node *temp, *p;
    temp = (struct Node*)malloc(sizeof(struct Node));
    temp->info = data;

    p = head;
    while(p->next != NULL)
        p = p->next;

    p->next = temp;
    temp->next = NULL;
}

void createList(struct Node *head)
{
    int i, n, data;

    printf("Enter the number of nodes: ");
    scanf("%d",&n);

    for(i = 1; i <= n; i++)
    {
        printf("Enter the next element to be inserted: ");
        scanf("%d",&data);
        insertAtEnd(head,data);
    }
}

void insertBefore(struct Node *head,int data,int x)
{
    struct Node *p, *temp;

    // Find pointer to predecessor of node containing x
    p = head;
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
}

void insertAtPosition(struct Node *head,int data,int k)
{
    int i;
    struct Node *p, *temp;

    p = head;
    for(i = 1; i <= k-1 && p != NULL; i++) // find a pointer to k-1 node
        p = p->next;

    if(p == NULL)
        printf("You can insert only up to %dth position\n",i-1);
    else
    {
        temp = (struct Node*)malloc(sizeof(struct Node));
        temp->info = data;
        temp->next = p->next;
        p->next = temp;
    }
}

void deleteNode(struct Node *head,int x)
{
    struct Node *temp, *p;

    p = head;
    while(p->next != NULL)
    {
        if(p->next->info == x)
            break;
        p = p->next;
    }
    if(p->next == NULL)
        printf("Element %d not found\n\n",x);
    else
    {
        temp = p->next;
        p->next = temp->next;
        free(temp);
    }
}

void reverse(struct Node *head)
{
    struct Node  *prev, *ptr, *next;
    prev = NULL;
    ptr = head->next;

    while(ptr != NULL)
    {
        next = ptr->next;
        ptr->next = prev;  // NULL
        prev = ptr;
        ptr = next;
    }
    head->next = prev;
}
