#include <stdio.h>
#include <stdlib.h>
#define MAX 10

int a[MAX];
int front, rear;

void initializeQueue();
int isEmpty();
int isFull();
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
    front = rear = -1;
}

int isEmpty()
{
    return (front == -1 || front == rear+1) ? 1 : 0;
}

int isFull()
{
    return (rear == MAX+1) ? 1 : 0;
}

int size()
{
    if(isEmpty())
        return 0;
    else
        return rear-front+1;
}

int peek()
{
    if(isEmpty())
    {
        printf("Queue Underflow\n");
        exit(1);
    }
    return a[front];
}

void enqueue(int x)
{
    if(isFull())
    {
        printf("Queue Overflow\n");
        return;
    }

    if(front == -1)
        front = 0;

    rear = rear+1;
    a[rear] = x;
}

int dequeue()
{
    int x;
    if(isEmpty())
    {
        printf("Queue Underflow\n");
        exit(1);
    }

    x = a[front];
    front = front+1;
    return x;
}

void display()
{
    int i;
    if(isEmpty())
    {
        printf("Queue is empty\n");
        return;
    }
    printf("Queue is :\n\n");
    for(i = front; i <= rear; i++)
        printf("%d ",a[i]);

    printf("\n\n");
}
