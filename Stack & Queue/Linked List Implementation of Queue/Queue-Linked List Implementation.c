#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int info;
    struct Node *next;
};

struct Node *front, *rear;  // Double ended linked list

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
    front = rear = NULL;
}

int isEmpty()
{
    return (front == NULL) ? 1 : 0;
}

int size()
{
    int s;
    struct Node *p = front;
    while(p != NULL)
    {
        p = p->next;
        s++;
    }
    return s;
}

int peek()
{
    if(isEmpty())
    {
        printf("Queue Underflow\n");
        exit(1);
    }
    return front->info;
}

void enqueue(int x)
{
    struct Node *temp;
    temp = (struct Node *)malloc(sizeof(struct Node));
    if(temp == NULL)
    {
        printf("Memory not available\n");
        return;
    }
    temp->info = x;
    temp->next = NULL;

    if(front == NULL) // isEmpty()
        front = temp; //rear = front = temp;
    else
        rear->next = temp;

    rear = temp;
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
    temp = front;
    x = temp->info;
    front = front->next;
    free(temp);

    return x;
}

void display()
{
    struct Node *p;
    p = front;
    if(isEmpty())
    {
        printf("Queue is empty\n");
        return;
    }
    printf("Queue is :\n\n");
    while(p != NULL)
    {
        printf("%d ",p->info);
        p = p->next;
    }

    printf("\n\n");
}

