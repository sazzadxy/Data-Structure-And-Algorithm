#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int *item;
    int size;
    int top;
}Stack;

void init(Stack *, int);
void dealloc(Stack *);
void push(Stack *, int);
int pop(Stack *);
int getSize(Stack *);

void init(Stack *s, int size)
{
    s->top = -1;
    s->item = (int *) malloc(sizeof(int) * size);
    if(s->item == NULL){
        printf("Unable to allocate memory\n");
        exit(1);
    }
    s->size = size;
}

int getSize(Stack *s)
{
    return s->size;
}

void push(Stack *s, int value)
{
    if(s->top == s->size - 1){
        int *temp = (int *) malloc(sizeof(int) * s->size * 2);

        if(temp == NULL){
            printf("Stack Overflow!\n");
            return;
        }

        for(int i = 0; i < s->size; i++){
            temp[i] = s->item[i];
        }
        free(s->item);
        s->item = temp;
        s->size *= 2;
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

void dealloc(Stack *s)
{
    if(s->item != NULL)
        free(s->item);
    s->size = 0;
    s->top = -1;
}

int main()
{
    Stack s1;
    int n;
    printf("Enter the size of Stack: ");
    scanf("%d", &n);
    init(&s1,n);
    int choice, value;

    printf("Stack Operation\n");
    printf("1. Push\n");
    printf("2. Pop\n");
    printf("3. Exit\n");

    while(1){
        printf("Enter your choice: ");
        scanf("%d",&choice);
        printf("Current size of Stack: %d\n",getSize(&s1));

        switch(choice){
        case 1:
            printf("Enter value:");
            scanf("%d", &value);
            push(&s1,value);
            break;
        case 2:
            value = pop(&s1);
            if(value != -9999){
                printf("Popped value %d:\n",value);
            }
            break;
        case 3:
            dealloc(&s1);
            exit(0);
        default:
            printf("Invalid choice\n");
        }
    }
    return 0;
}

