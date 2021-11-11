#include <stdio.h>
#include <stdlib.h>
#define SIZE 100

typedef struct{
    char item[SIZE];
    int top;
}Stack;

void init(Stack *);
void dealloc(Stack *);
void push(Stack *, char);
char pop(Stack *);

int isEmpty(Stack *);
char stackTop(Stack *);
int openingMatch(char, char);
int checkExpr(char []);

void init(Stack *s)
{
    s->top = -1;
}

void push(Stack *s, char ch)
{
    if(s->top == SIZE - 1){
        printf("Stack overflow, terminating the program\n");
        exit(1);
        }
    s->item[++s->top] = ch;
}

char pop(Stack *s)
{
    if(s->top == -1){
        printf("Stack underflow, terminating the program\n");
        exit(1);
    }
    return s->item[s->top--];
}

int isEmpty(Stack *s)
{
    return s->top == -1;
}

char stackTop(Stack *s)
{
    if(isEmpty(s)){
        printf("Stack underflow, terminating the program\n");
        exit(1);
    }
    return s->item[s->top];
}

int openingMatch(char left, char right)
{
    int match = 0;

    switch(left){
    case '(':
        if(right == ')')
            match = 1;
        break;
    case '{':
        if(right == '}')
            match = 1;
        break;
    case '[':
        if(right == ']')
            match = 1;
        break;
    default:
        printf("Invalid symbol encountered, terminating the program\n");
        exit(1);
    }
    return match;
}

int checkExpr(char expr[])
{
    Stack s;
    init(&s);
    int error = 0;
    int i = 0;

    while(expr[i] != '\0'){
            char nextChar = expr[i];

            if(nextChar == '(' || nextChar == '{' || nextChar == '[')
                push(&s,nextChar);
            else if(nextChar == ')' || nextChar == '}' || nextChar == ']'){
                if(isEmpty(&s)){
                    error = 1;
                    break;
                }
                else if(openingMatch(stackTop(&s),nextChar)){
                    pop(&s);
                }
                else{
                    error = 1;
                    break;
                }
            }
            ++i;
    }

    if(!error && !isEmpty(&s))
       error = 1;

    return error;
}


int main()
{
   char expr[SIZE];
   printf("Input expression: ");
   scanf("%s",expr);

   if(checkExpr(expr)){
        printf("Does not contain well formed brackets\n");
   }
   else  printf("Contain well formed brackets\n");


    return 0;
}

