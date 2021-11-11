#include <stdio.h>
#include <stdlib.h>
#define MAX 5

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
    return (front == -1) ? 1 : 0;
}

int isFull()
{
    return ((front == 0 && rear == MAX-1) || (front == rear+1)) ? 1 : 0;
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

    if(rear == MAX-1)
        rear = 0;
    else
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

    if(front == rear)   // Queue has only one element
        front = rear == -1;
    else if(front == MAX-1)
        front = 0;
    else
        front = front+1;

    return x;
}

int size()
{
    int sz,i;

    if(isEmpty())
        return 0;
    if(isFull())
        return MAX;

    i = front;
    sz = 0;
    if(front <= rear)
    {
        while(i <= rear)
        {
            sz++;
            i++;
        }
    }
    else   // if front > rear, count from a[front] to a[MAX-1], then from a[0] to a[rear]
    {
        while(i <= MAX-1)
        {
            sz++;
            i++;
        }
        i = 0;
        while(i <= rear)
        {
            sz++;
            i++;
        }
    }

    return sz;
}

void display()
{
    int i;
    printf("front = %d, rear = %d\n",front,rear);
    if(isEmpty())
    {
        printf("Queue is empty\n");
        return;
    }
    printf("Queue is :\n\n");

    i = front;
    if(front <= rear)  // print a[front] to a[rear]
    {
        while(i <= rear)
            printf("%d ",a[i++]);
    }
    else   // if front > rear, print from a[front] to a[MAX-1], then from a[0] to a[rear]
    {
        while(i <= MAX-1)   // print a[front] to a[rear]
            printf("%d ",a[i++]);
        i = 0;
        while(i <= rear)   // print a[0] to arr[rear]
            printf("%d ",a[i++]);
    }
    printf("\n");
}

