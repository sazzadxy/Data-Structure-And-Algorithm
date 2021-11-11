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
int isOverflow(Stack *);
int isUnderflow(Stack *);
void printBinary(unsigned int);

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

int isOverflow(Stack *s)
{
    return s->top == s->size - 1;
}

int isUnderflow(Stack *s)
{
    return s->top == -1;
}

int getSize(Stack *s)
{
    return s->size;
}

void push(Stack *s, int value)
{
    if(isOverflow(s)){
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
    if(isUnderflow(s)){
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

void printBinary(unsigned int n)
{
    Stack s;
    const int BASE = 2;
    init(&s,n);
    int temp = n;

    while(n > 0){
        int rem = n % BASE;
        push(&s,rem);
        n /= BASE;
    }

    printf("Binary equivalent of %d is: \n", temp);
    while(!isUnderflow(&s)){
            printf("%d",pop(&s));
        }
    dealloc(&s);
}

int main()
{
    printf("Enter a decimal number to convert binary: ");
    unsigned int n;
    scanf("%d", &n);
    printBinary(n);
    return 0;
}


