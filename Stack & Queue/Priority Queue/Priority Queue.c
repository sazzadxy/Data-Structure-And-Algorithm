#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int priority;
    int info;
    struct Node *next;
};

struct Node *front;

void initializeQueue();
void insert(int element, int elementPriority);
int Delete();
int isEmpty();
void display();

int main()
{
    int choice, element, elementPriority;

    initializeQueue();

    while(1)
    {
        printf("    Priority Queue\n");
        printf("------------------------\n");
        printf("1. Insert a new element\n");
        printf("2. Delete an element\n");
        printf("3. Display the queue\n");
        printf("4. Quit\n");
        printf("Enter your choice : ");
        scanf("%d",&choice);
        if(choice == 4)
            break;

        switch(choice)
        {
        case 1:
            printf("Enter the element to be inserted : ");
            scanf("%d",&element);
            printf("Enter its priority : ");
            scanf("%d",&elementPriority);
            insert(element,elementPriority);
            break;
        case 2:
            printf("Deleted element is : %d\n",Delete());
            break;
        case 3:
            display();
            break;
        default:
            printf("Wrong choice\n");
        }
    }
    return 0;
}

void initializeQueue()
{
    front = NULL;
}

int isEmpty()
{
    if(front == NULL)
        return 1;
    else
        return 0;
}

void insert(int element, int elementPriority)
{
    struct Node *temp, *p;

    temp = (struct Node *)malloc(sizeof(struct Node));

    if(temp == NULL)
    {
        printf("Memory not available\n");
        return;
    }
    temp->info = element;
    temp->priority = elementPriority;

    // Queue is empty or element to be added has priority more than first element, i.e, 1 < 2
    if(isEmpty() || elementPriority < front->priority)
    {
        temp->next = front;
        front = temp;
    }
    else
    {
        p = front;
        while(p->next != NULL && p->next->priority <= elementPriority)
            p = p->next;

        temp->next = p->next;
        p->next = temp;
    }
}

int Delete()
{
    struct Node *temp;
    int element;

    if(isEmpty())
    {
        printf("Queue Underflow\n");
        exit(1);
    }
    else
    {
        temp = front;
        element = temp->info;
        front = temp->next;
        free(temp);
    }

    return element;
}

void display()
{
    struct Node *ptr;
    ptr = front;

    if(isEmpty())
        printf("Queue is empty\n");
    else
    {
        printf("Queue is :\n");
        printf("Priority   element\n");
        while(ptr != NULL)
        {
            printf("%5d  %5d\n", ptr->priority, ptr->info);
            ptr = ptr->next;
        }
    }
    printf("\n");
}

