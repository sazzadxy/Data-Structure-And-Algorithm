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
struct Node *insertAfter(struct Node *last,int data,int item);
struct Node *deleteNode(struct Node *last,int data);

int main()
{
    struct Node *last = NULL;
    int choice, data, x;

    last = createList(last);

    while(1)
    {
        printf("\n");
        printf("\tCircular Linked List\t\n");
        printf("\t------------------\t\n");
        printf("1.Display list\n");
        printf("2.Insert in empty list\n");
        printf("3.Insert in the beginning\n");
        printf("4.Insert at the end\n");
        printf("5.Insert after a node\n");
        printf("6.Delete a node\n");
        printf("7.Quit\n");
        printf("Enter your choice: ");
        scanf("%d",&choice);

        if(choice == 7)
            break;

        switch(choice)
        {
        case 1:
            displayList(last);
            break;
        case 2:
            printf("Enter the element to be inserted: ");
            scanf("%d",&data);
            last = insertInEmptyList(last,data);
            break;
        case 3:
            printf("Enter the element to be inserted: ");
            scanf("%d",&data);
            last = insertInBeginnig(last,data);
            break;
        case 4:
            printf("Enter the element to be inserted: ");
            scanf("%d",&data);
            last = insertAtEnd(last,data);
            break;
        case 5:
            printf("Enter the element to be inserted: ");
            scanf("%d",&data);
            printf("Enter the element after which to insert: ");
            scanf("%d",&x);
            last = insertAfter(last,data,x);
            break;
        case 6:
            printf("Enter the element to be deleted: ");
            scanf("%d",&data);
            last = deleteNode(last,data);
            break;
        default:
            printf("Wrong choice\n");
        }
    }
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

struct Node *insertInBeginnig(struct Node *last,int data)
{
    struct Node *temp;
    temp = (struct Node*)malloc(sizeof(struct Node));
    temp->info = data;

    temp->next = last->next;
    last->next = temp;
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

struct Node *insertAfter(struct Node *last,int data,int x)
{
    struct Node *p, *temp;

    p = last->next;
    do
    {
        if(p->info == x)
            break;
        p = p->next;
    }while(p != last->next);

    if(p == last->next && p->info != x)
        printf("%d not present in the list\n",x);
    else
    {
        temp = (struct Node*)malloc(sizeof(struct Node));
        temp->info = data;

        temp->next = p->next;
        p->next = temp;
        if(p == last)
            last = temp;
    }
    return last;
}

struct Node *deleteNode(struct Node *last,int x)
{
   struct Node *temp, *p;
   if(last == NULL)
   {
       printf("List is empty\n");
       return last;
   }

   // Deletion of only node
   if(last->next == last && last->info == x)
   {
       temp = last;
       last = NULL;
       free(temp);
       return last;
   }

   // Deletion of first node
   if(last->next->info == x)
   {
       temp = last->next;
       last->next = temp->next;
       free(temp);
       return last;
   }

   p = last->next;
   while(p->next != last)
    {
        if(p->next->info == x)
            break;
        p = p->next;
   }

   if(p->next != last) // Node to be deleted is in between
   {
       temp = p->next;
       p->next = temp->next;
       free(temp);
   }
   else
   {
       if(last->info == x) // Node to be deleted is last node
       {
            temp = last;
            p->next = last->next;
            last = p;
            free(temp);
       }
       else
            printf("Element %d not found\n",x);
    }
    return last;
}


