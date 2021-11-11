
#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int info;
    struct Node *next;
};

struct Node *rear;  // Double ended linked list

void initializeQueue();
int isEmpty();
int size();
int peek();
void enqueue(int x);
int dequeue();
void display();

int main()
{
    int choice, x;
    initializeQueue();

    while(1){
        printf("1.Insert an element on the queue\n");
        printf("2.Delete an element from the queue\n");
        printf("3.Display element at the front\n");
        printf("4.Display all the elements of the queue \n");
        printf("5.Display size of the queue\n");
        printf("6.Quit\n");
        printf("Enter your choice : \n");
        scanf("%d",&choice);
        if(choice == 6)
            break;

        switch(choice){
        case 1: printf("Enter the element to be inserted :");
            scanf("%d", &x);
            enqueue(x);
            break;
        case 2:
            x = dequeue();
            printf("Element deleted is : %d\n",x);
            break;
        case 3:
            printf("Element at the front is : %d\n",peek());
            break;
        case 4:
            display();
            break;
        case 5:
            printf("Size of queue = %d\n",size());
            break;
        default:
            printf("Wrong choice\n");
        }
        printf("\n");
    }

    return 0;
}

void initializeQueue()
{
    rear = NULL;
}

int isEmpty()
{
    return (rear == NULL) ? 1 : 0;
}

int size()
{
    int s = 0;
    struct Node *p;
    if(isEmpty())
        return 0;

    p = rear->next;

    do
    {
        s++;
        p = p->next;
    }while(p != rear->next);
    return s;
}

int peek()
{
    if(isEmpty())
    {
        printf("Queue Underflow\n");
        exit(1);
    }
    return rear->next->info;
}

void enqueue(int x)
{
    struct Node *temp;
    temp = (struct Node *)malloc(sizeof(struct Node));
    temp->info = x;
    if(temp == NULL)
    {
        printf("Memory not available\n");
        return;
    }

    if(isEmpty())
    {
        rear = temp;
        rear->next = rear;

    }
    else
    {
        temp->next = rear->next;
        rear->next = temp;
        rear = temp;
    }
}

int dequeue()
{
    int x;
    struct Node *temp;
    if(isEmpty())
    {
        printf("Queue Underflow\n");
        exit(1);
    }

    if(rear->next == rear) // If only one element
    {
        temp = rear;
        rear = NULL;
    }
    else
    {
        temp = rear->next;
        rear->next = temp->next;
    }

    x = temp->info;
    free(temp);

    return x;
}

void display()
{
    struct Node *p;

    if(isEmpty())
    {
        printf("Queue is empty\n");
        return;
    }
    printf("Queue is :\n\n");
    p = rear->next;
    do
    {
        printf("%d ",p->info);
        p = p->next;
    }while(p != rear->next);

    printf("\n");
}

