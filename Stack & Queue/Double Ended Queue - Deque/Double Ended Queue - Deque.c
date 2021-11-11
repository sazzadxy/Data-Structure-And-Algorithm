#include <stdio.h>
#include <stdlib.h>
#define MAX 10

/*
    Insert at front end - front is decreased. if front is 0, make it MAX-1. if front = rear = -1 make both 0
    Insert at rear end - rear is increased. if rear is MAX-1, make it 0. if front is -1 make it 0
    Delete from front end - front is increased. if front is MAX-1, make it 0
    Delete from rear end - rear is decreased. if rear is 0, make it MAX-1
*/

int a[MAX];
int front, rear;

void initializeQueue();
int isEmpty();
int isFull();
void insertFront(int x);
void insertRear(int x);
int deleteFront();
int deleteRear();
void display();

int main()
{
    int choice, x;
    initializeQueue();

    while(1){
        printf("1.Insert at the front end\n");
        printf("2.Insert at the rear end\n");
        printf("3.Delete from the front end\n");
        printf("4.Delete from the rear end\n");
        printf("5.Display all the elements of deque\n");
        printf("6.Quit\n");
        printf("Enter your choice : \n");
        scanf("%d",&choice);
        if(choice == 6)
            break;

        switch(choice){
        case 1:
            printf("Enter the element to be inserted: ");
            scanf("%d", &x);
            insertFront(x);
            break;
        case 2:
            printf("Enter the element to be inserted: ");
            scanf("%d", &x);
            insertRear(x);
            break;
        case 3:
            printf("Element deleted from the front end is: %d\n",deleteFront());
            break;
        case 4:
            printf("Element deleted from the rear end is: %d\n",deleteRear());
            break;
        case 5:
            display();
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

void insertFront(int x)
{
    if(isFull())
    {
        printf("Queue Overflow\n");
        return;
    }
    if(front == -1)
        front = rear = 0;

    else if(front == 0)
        front = MAX-1;
    else
        front = front-1;
    a[front] = x;
}

void insertRear(int x)
{
    if(isFull())
    {
        printf("Queue Overflow\n");
        return;
    }
    if(front == -1)
        front = 0;

    else if(rear == MAX-1)
        rear = 0;
    else
        rear = rear+1;
    a[rear] = x;
}

int deleteFront()
{
    int x;
    if(isEmpty())
    {
        printf("Queue Underflow\n");
        exit(1);
    }
    x = a[front];

    if(front == rear)   // Queue has only one element
        front = rear = -1;
    else if(front == MAX-1)
        front = 0;
    else
        front = front+1;

    return x;
}

int deleteRear()
{
    int x;
    if(isEmpty())
    {
        printf("Queue Underflow\n");
        exit(1);
    }
    x = a[rear];

    if(front == rear)   // Queue has only one element
        front = rear = -1;
    else if(rear == 0)
        rear = MAX-1;
    else
        rear = rear-1;

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


