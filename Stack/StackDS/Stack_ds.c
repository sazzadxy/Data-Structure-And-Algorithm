#include <stdio.h>
#include <stdlib.h>
#define SIZE 10

typedef struct{
    int top;
    int item[SIZE];
}Stack;

void init(Stack *);
void push(Stack *, int);
int pop(Stack *);

void push(Stack *s, int value)
{
    if(s->top == SIZE - 1){
        printf("Stack Overflow!\n");
        return;
    }
    s->top++;
    s->item[s->top] = value;
}

int pop(Stack *s)
{
    if(s->top == -1){
        printf("Stack Underflow!\n");
        return -9999;
    }
    int value;
    value = s->item[s->top];
    s->top--;
    return value;
}

void init(Stack *s)
{
    s->top = -1;
}

int main()
{
    Stack s1;
    init(&s1);
    int choice, value;
    printf("Stack Operation\n");
    while(1){
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Exit\n");
        printf("Enter your choice\n");
        scanf("%d",&choice);

        switch(choice){
        case 1: printf("Enter value:");
            scanf("%d", &value);
            push(&s1,value);
            break;
        case 2:
            value = pop(&s1);
            if(value != -9999){
                printf("Popped value %d:",value);
            }
            break;
        case 3:
            exit(0);
        default:
            printf("Invalid choice\n");
        }
    }
    return 0;
}


//    push(&s1,100);
//    push(&s1,200);
//    push(&s1,300);
//    push(&s1,400);
//    push(&s1,500);
//    push(&s1,600);
//    push(&s1,700);
//
//    printf("Value popped from s1 is %d\n", pop(&s1));
//    printf("Value popped from s1 is %d\n", pop(&s1));
//    printf("Value popped from s1 is %d\n", pop(&s1));
//    printf("Value popped from s1 is %d\n", pop(&s1));
//    printf("Value popped from s1 is %d\n", pop(&s1));
//    printf("Value popped from s1 is %d\n", pop(&s1));
//    printf("Value popped from s1 is %d\n", pop(&s1));


