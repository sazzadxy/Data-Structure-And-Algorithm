#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int info;
    struct Node *next;
};

struct Node *top;

void initializeStack();
int isEmpty();
int size();
int peek();
void push(int x);
int pop();
void display();

int main()
{
    int choice, x;
    initializeStack();

    while(1){
        printf("1.Push an element on the stack\n");
        printf("2.Pop an element from the stack\n");
        printf("3.Display the top element\n");
        printf("4.Display all the stack element\n");
        printf("5.Display size of the stack\n");
        printf("6.Quit\n");
        printf("Enter your choice : \n");
        scanf("%d",&choice);
        if(choice == 6)
            break;

        switch(choice){
        case 1: printf("Enter the element to be pushed :");
            scanf("%d", &x);
            push(x);
            break;
        case 2:
            x = pop();
            printf("Popped element is : %d\n",x);
            break;
        case 3:
            printf("Element at the top is : %d\n",peek());
            break;
        case 4:
            display();
            break;
        case 5:
            printf("Size of stack = %d\n",size());
            break;
        default:
            printf("Wrong choice\n");
        }
        printf("\n");
    }

    return 0;
}

void initializeStack()
{
    top = NULL;
}

int isEmpty()
{
    if(top == NULL)
        return 1;
    else
        return 0;
}

int size()
{
    int s = 0;
    struct Node *p = top;

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
        printf("Stack Underflow\n");
        exit(1);
    }
    return top->info;
}

void push(int x)
{
    struct Node *temp;
    temp = (struct Node*)malloc(sizeof(struct Node));

    if(temp == NULL)
    {
        printf("No memory : Stack Overflow\n");
        return;
    }
    temp->info = x;
    temp->next = top;
    top = temp;
}

int pop()
{
    struct Node *temp;
    int x;

    if(isEmpty())
    {
        printf("Stack Underflow\n");
        exit(1);
    }
    temp = top;
    x = temp->info;
    top = top->next; // temp->next;
    free(temp);
    return x;
}

void display()
{
    struct Node *p;
    p = top;

    if(isEmpty())
    {
        printf("Stack is empty\n");
        return;
    }

    printf("Stack is: \n\n");
    while(p != NULL)
    {
        printf(" %d\n",p->info);
        p = p->next;
    }
    printf("\n");
}
